#include "RomModel.h"
#include "MachineItem.h"
#include "Settings.h"
#include "Utils.h"

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QDir>
#include <QIcon>

#include <QDebug>

class RomModelThread : public QThread
{
	Q_OBJECT
	
public:
	RomModelThread( QObject* parent )
		: QThread( parent )
	{
		qRegisterMetaType<QFileInfoList>( "QFileInfoList" );
		mStop = false;
		mRestart = false;
		mMachine = 0;
		mSettings = 0;
	}
	
	virtual ~RomModelThread()
	{
		QMutexLocker locker( &mMutex );
		mStop = true;
		locker.unlock();
		wait();
	}
	
	QFileInfoList getRecursiveFiles( QDir fromDir, const QStringList& filters )
	{
		QFileInfoList files;
		
		foreach ( QFileInfo file, fromDir.entryInfoList( QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst | QDir::Name ) )
		{
			if ( file.isFile() && ( filters.isEmpty() || QDir::match( filters, file.fileName() ) ) )
			{
				files << file;
			}
			else if ( file.isDir() )
			{
				fromDir.cd( file.filePath() );
				files << getRecursiveFiles( fromDir, filters );
				fromDir.cdUp();
			}
		}
		
		return files;
	}
	
	static bool lessThanFileInfo( const QFileInfo& left, const QFileInfo& right )
	{
		int result = QString::compare( left.completeBaseName(), right.completeBaseName(), Qt::CaseInsensitive );
		
		if ( result < 0 )
		{
			return true;
		}
		else if ( result > 0 )
		{
			return false;
		}
		else
		{
			return true;
		}
	}

public slots:
	void getRoms( const MachineItem* machine, const Settings* settings, const QString& searchWildcard )
	{
		{
			QMutexLocker locker( &mMutex );
			mStop = false;
			mRestart = isRunning();
			mMachine = machine;
			mSettings = settings;
			mSearchWildcard = searchWildcard.trimmed();
		}
		
		if ( !isRunning() )
		{
			start();
		}
	}

protected:
	QMutex mMutex;
	bool mStop;
	bool mRestart;
	const MachineItem* mMachine;
	const Settings* mSettings;
	QString mSearchWildcard;
	
	virtual void run()
	{
		QString mask;
		
		{
			QMutexLocker locker( &mMutex );
			mRestart = false;
			mask = mSearchWildcard.isEmpty() ? "*" : mSearchWildcard.prepend( "*" ).append( "*" );
		}
		
		QStringList filters;
		
		foreach ( const iDevice& device, mMachine->infos().devices() )
		{
			foreach ( const QString& extension, device.extensions() )
			{
				filters << QString( "%1.%2" ).arg( mask ).arg( extension );
				
				{
					QMutexLocker locker( &mMutex );
					
					if ( mRestart )
					{
						return;
					}
				}
			}
		}
		
		forever
		{
			const QStringList paths = QStringList( mSettings->romsPath( mMachine->infos().data( MachineInfos::Name ), mMachine->infos().data( MachineInfos::CloneOf ) ) );
			
			QFileInfoList files;
			QDir dir;
			
			foreach ( const QString& path, paths )
			{
				dir.setPath( path );
				files << getRecursiveFiles( dir, filters );
				
				{
					QMutexLocker locker( &mMutex );
					
					if ( mStop )
					{
						return;
					}
					else if ( mRestart )
					{
						break;
					}
				}
			}
			
			{
				QMutexLocker locker( &mMutex );
				
				if ( mRestart )
				{
					mRestart = false;
					locker.unlock();
					continue;
				}
			}
			
			qSort( files.begin(), files.end(), lessThanFileInfo );
			
			emit queryFinished( files );
			break;
		}
	}

signals:
	void queryFinished( const QFileInfoList& files );
};

RomModel::RomModel( QObject* parent )
	: QAbstractItemModel( parent )
{
	mThread = new RomModelThread( this );
	
	connect( mThread, SIGNAL( queryFinished( const QFileInfoList& ) ), this, SLOT( queryFinished( const QFileInfoList& ) ) );
}

RomModel::~RomModel()
{
}

int RomModel::columnCount( const QModelIndex& parent ) const
{
	Q_UNUSED( parent );
	return 4;
}

QVariant RomModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if ( orientation == Qt::Horizontal )
	{
		switch ( role )
		{
			case Qt::DisplayRole:
			{
				switch ( section )
				{
					case 0:
						return tr( "Screenshot" );
						break;
					case 1:
						return tr( "Name" );
						break;
					case 2:
						return tr( "Size" );
						break;
					case 3:
						return tr( "Type" );
						break;
				}
				break;
			}
		}
	}
	
	return QAbstractItemModel::headerData( section, orientation, role );
}

QVariant RomModel::data( const QModelIndex& index, int role ) const
{
	const QModelIndex parentIndex = index.parent();
	
	if ( !index.isValid() || index.row() > rowCount( parentIndex ) || index.column() > columnCount( parentIndex ) )
	{
		return QVariant();
	}
	
	const int row = index.row();
	const int column = index.column();
	
	switch ( column )
	{
		case 0:
			if ( role == Qt::DecorationRole )
			{
				QString fn;// = QString( "%1/.mess/snap/gamegeaj/%2.png" ).arg( QDir::homePath() ).arg( "0000" );
				return QIcon( fn );
			}
			break;
		case 1:
			if ( role == Qt::DisplayRole )
			{
				return mFiles.at( row ).completeBaseName();
			}
			break;
		case 2:
			if ( role == Qt::DisplayRole )
			{
				return Utils::fileSizeToString( mFiles.at( row ).size() );
			}
			break;
		case 3:
			if ( role == Qt::DisplayRole )
			{
				return mFiles.at( row ).suffix();
			}
			break;
	}
	
	return QVariant();
}

QModelIndex RomModel::index( int row, int column, const QModelIndex& parent ) const
{
	if ( row < rowCount( parent ) && column < columnCount( parent ) )
	{
		return createIndex( row, column, row );
	}
	
	return QModelIndex();
}

QModelIndex RomModel::parent( const QModelIndex& index ) const
{
	Q_UNUSED( index );
	return QModelIndex();
}

int RomModel::rowCount( const QModelIndex& parent ) const
{
	Q_UNUSED( parent );
	return mFiles.count();
}

bool RomModel::hasChildren( const QModelIndex& parent ) const
{
	return parent.isValid() ? false : !mFiles.isEmpty();
}

QString RomModel::filePath( const QModelIndex& index ) const
{
	if ( index.isValid() )
	{
		return mFiles.at( index.row() ).absoluteFilePath();
	}
	
	return QString::null;
}

void RomModel::refresh( const MachineItem* machine, const Settings* settings, const QString& searchWildcard )
{
	mFiles.clear();
	reset();
	mThread->getRoms( machine, settings, searchWildcard );
}

void RomModel::queryFinished( const QFileInfoList& files )
{
	mFiles = files;
	
	reset();
	emit ready();
}

#include "RomModel.moc"
