#ifndef ROMMODEL_H
#define ROMMODEL_H

#include <QAbstractItemModel>
#include <QFileInfo>

class RomModelThread;
class MachineItem;
class Settings;

class RomModel : public QAbstractItemModel
{
	Q_OBJECT
	
public:
	RomModel( QObject* parent );
	virtual ~RomModel();
	
	virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
	virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
	virtual QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const;
	virtual QModelIndex parent( const QModelIndex& index ) const;
	virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
	virtual bool hasChildren( const QModelIndex& parent = QModelIndex() ) const;
	
	QString filePath( const QModelIndex& index ) const;

public slots:
	void refresh( const MachineItem* machine, const Settings* settings, const QString& searchWildcard );

protected:
	RomModelThread* mThread;
	QFileInfoList mFiles;

protected slots:
	void queryFinished( const QFileInfoList& files );

signals:
	void ready();
};

#endif // ROMMODEL_H
