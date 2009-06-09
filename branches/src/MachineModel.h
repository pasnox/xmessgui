#ifndef MACHINEMODEL_H
#define MACHINEMODEL_H

#include <QAbstractItemModel>
#include <QDomDocument>

class MachineItem;
typedef QList<class MachineItem*> MachineItemList;

struct MachinesCount
{
	MachinesCount()
	{ total = 0; unique = 0; clones = 0; }
	
	MachinesCount& operator+=( const MachinesCount& other )
	{
		total += other.total;
		unique += other.unique;
		clones += other.clones;
		
		return *this;
	}
	
	int total;
	int unique;
	int clones;
};

class MachineModel : public QAbstractItemModel
{
	Q_OBJECT
	
public:
	MachineModel( QObject* parent = 0 );
	virtual ~MachineModel();
	
	QVariant data( const QModelIndex& index, int role ) const;
	Qt::ItemFlags flags( const QModelIndex& index ) const;
	QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const;
	QModelIndex parent( const QModelIndex& child ) const;
	int rowCount( const QModelIndex& parent = QModelIndex() ) const;
	int columnCount( const QModelIndex& parent = QModelIndex() ) const;
	
	MachineItem* rootItem() const;
	MachineItemList rootItems() const;
	MachineItem* itemFromIndex( const QModelIndex& index ) const;
	QModelIndex itemToIndex( MachineItem* item ) const;
	MachineItem* machineItem( const QString& name ) const;
	QModelIndex machineIndex( const QString& name ) const;
	void setDocument( const QDomDocument& document );
	
	void setIconsPath( const QString& path );
	QString iconsPath() const;
	
	MachinesCount count( MachineItem* parent = 0 ) const;
	
protected:
	QString mIconsPath;
	QDomDocument mDocument;
	QMap<QString, MachineItem*> mMachineItems;
	
	void createItems();
	void arrangeItems();
	void clear( const QDomDocument& document = QDomDocument() );

signals:
	void ready();
};

#endif // MACHINEMODEL_H
