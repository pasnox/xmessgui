#include "ProcessQuery.h"
#include "Settings.h"
#include "MachineItem.h"

#include <QDir>
#include <QApplication>
#include <QInputDialog>
#include <QDebug>

ProcessQuery::ProcessQuery( Settings* settings, QObject* parent )
	: QProcess( parent )
{
	Q_ASSERT( settings );
	mSettings = settings;
	
	setObjectName( "processQuery" );
	setReadChannelMode( QProcess::MergedChannels );
	mCurrentTask = ProcessQuery::IDLE;
	
	connect( this, SIGNAL( started() ), this, SLOT( _q_started() ) );
	connect( this, SIGNAL( error( QProcess::ProcessError ) ), this, SLOT( _q_error( QProcess::ProcessError ) ) );
	connect( this, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( _q_finished( int, QProcess::ExitStatus ) ) );
}

ProcessQuery::~ProcessQuery()
{
}

void ProcessQuery::startMachine( MachineItem* machine )
{
	mMachineRomPair = MachineRomPair( machine, QString::null );
	addTask( ProcessQuery::StartMachine );
}

void ProcessQuery::startMachineRom( MachineItem* machine, const QString& filePath )
{
	mMachineRomPair = MachineRomPair( machine, filePath );
	addTask( ProcessQuery::StartMachineRom );
}

bool ProcessQuery::startNextTask()
{
	if ( mTasks.isEmpty() )
	{
		return false;
	}
	
	mCurrentTask = mTasks.dequeue();
	QStringList args;
	
	switch ( mCurrentTask )
	{
		case ProcessQuery::StartMachine:
		case ProcessQuery::StartMachineRom:
			// machine
			args << mMachineRomPair.first->infos().data( MachineInfos::Name );
			args << "-rompath" << mSettings->stringValue( Settings::Bios );
			
			// performance
			if ( mSettings->boolValue( Settings::Multithreading ) )
			{
				args << "-multithreading";
			}
			
			if ( mSettings->boolValue( Settings::SDLFPS ) )
			{
				args << "-sdlvideofps";
			}
			
			// video
			args << "-video";
			args << mSettings->stringValue( Settings::VideoMode );
			
			if ( mSettings->stringValue( Settings::VideoMode ) == "soft" )
			{
				args << "-scalemode" << mSettings->stringValue( Settings::ScaleMode );
			}
			
			if ( !mSettings->boolValue( Settings::FullScreen ) )
			{
				args << "-window";
			}
			
			if ( mSettings->boolValue( Settings::Maximize ) )
			{
				args << "-maximize";
			}
			
			if ( mSettings->boolValue( Settings::KeepAspectRatio ) )
			{
				args << "-keepaspect";
			}
			
			if ( mSettings->boolValue( Settings::AllowDoubleStretchFactors ) )
			{
				args << "-unevenstretch";
			}
			
			if ( mSettings->boolValue( Settings::WaitVBLANK ) )
			{
				args << "-waitvsync";
			}
			
			// misc
			if ( mSettings->boolValue( Settings::SkipGameInformations ) )
			{
				args << "-skip_gameinfo";
			}
			
			if ( mSettings->boolValue( Settings::SkipWarnings ) )
			{
				args << "-skip_warnings";
			}
			
			if ( mSettings->boolValue( Settings::Cheat ) )
			{
				args << "-cheat";
			}
			
			// states
			if ( mSettings->boolValue( Settings::AutoSave ) )
			{
				args << "-autosave";
			}
			
			// device
			if ( mCurrentTask == ProcessQuery::StartMachineRom )
			{
				bool found = false;
				QStringList instances;
				
				foreach ( const iDevice& device, mMachineRomPair.first->infos().devices() )
				{
					const QStringList filters = device.extensions().replaceInStrings( QRegExp( "^(.*)$" ), "*.\\1" );
					const QString instance = device.data( iDevice::Name );
					instances << instance;
					
					if ( QDir::match( filters, mMachineRomPair.second ) )
					{
						found = true;
						args << QString( "-%1" ).arg( instance );
						args << mMachineRomPair.second;
						break;
					}
				}
				
				if ( !found )
				{
					bool ok;
					const QString instance = QInputDialog::getItem( qApp->activeWindow(), tr( "Devices..." ), tr( "Choose the device to use:" ), instances, 0, true, &ok );
					
					if ( ok && !instance.isEmpty() )
					{
						args << QString( "-%1" ).arg( instance );
						args << mMachineRomPair.second;
					}
					else
					{
						emit log( tr( "Default device not found, user does not choose a proposed device: start aborted." ) );
						return false;
					}
				}
			}
			
			break;
		case ProcessQuery::ListXml:
			args << "-listxml";
			break;
		case ProcessQuery::VerifyRoms:
			args << "-verifyroms";
			break;
		case ProcessQuery::IDLE:
			return false;
			break;
		default:
			Q_ASSERT( 0 );
			return false;
			break;
	}
	
	for ( int i = 0; i < args.count(); i++ )
	{
		QString arg = args.at( i );
		
		if ( arg.contains( " " ) )
		{
			arg.prepend( "\"" ).append( "\"" );
			args[ i ] = arg;
		}
	}
	
	emit log( tr( "Running command: %1 %2" ).arg( mSettings->stringValue( Settings::Binary ) ).arg( args.join( " " ) ) );
	start( mSettings->stringValue( Settings::Binary ), args );
	return true;
}

bool ProcessQuery::addTask( ProcessQuery::Task task )
{
	if ( mTasks.contains( task ) )
	{
		return false;
	}
	
	mTasks.enqueue( task );
	
	if ( state() == QProcess::NotRunning )
	{
		startNextTask();
	}
	
	return true;
}

void ProcessQuery::handleNormalExit()
{
	switch ( mCurrentTask )
	{
		case ProcessQuery::StartMachine:
			break;
		case ProcessQuery::StartMachineRom:
			break;
		case ProcessQuery::ListXml:
		{
			QDomDocument document;
			const QByteArray datas = readAll();
			QString errorMsg;
			int errorLine;
			int errorColumn;
			bool ok = document.setContent( datas, &errorMsg, &errorLine, &errorColumn );
			
			emit listXmlFinished( document, !ok, errorMsg, QPoint( errorColumn, errorLine ) );
			break;
		}
		case ProcessQuery::VerifyRoms:
		{
			const QString datas = QString::fromLocal8Bit( readAll() );
			
			emit verifyRomsFinished( datas );
			break;
		}
		case ProcessQuery::IDLE:
			break;
	}
}

void ProcessQuery::_q_started()
{
	emit started( mCurrentTask );
}

void ProcessQuery::_q_error( QProcess::ProcessError err )
{
	emit error( mCurrentTask, err );
}

void ProcessQuery::_q_finished( int exitCode, QProcess::ExitStatus exitStatus )
{
	Q_UNUSED( exitCode );
	
	switch ( exitStatus )
	{
		case QProcess::NormalExit:
			handleNormalExit();
			break;
		case QProcess::CrashExit:
			break;
	}
	
	QString buffer = QString::fromLocal8Bit( readAll() );
	
	if ( !buffer.isEmpty() )
	{
		emit log( buffer );
	}
	
	startNextTask();
}

void ProcessQuery::listXml()
{
	addTask( ProcessQuery::ListXml );
}

void ProcessQuery::verifyRoms()
{
	addTask( ProcessQuery::VerifyRoms );
}
