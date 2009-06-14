#include "MachineModel.h"
#include "MachineItem.h"

#include <QIcon>
#include <QDebug>

MachineModel::MachineModel( QObject* parent )
	: QAbstractItemModel( parent )
{
	const int lighter = 180;
	QPixmap pixWorking( QSize( 16, 16 ) );
	pixWorking.fill( QColor( Qt::green ).lighter( lighter ) );
	QPixmap pixImperfect( QSize( 16, 16 ) );
	pixImperfect.fill( QColor( Qt::blue ).lighter( lighter ) );
	QPixmap pixNotWorking( QSize( 16, 16 ) );
	pixNotWorking.fill( QColor( Qt::red ).lighter( lighter ) );
	mIconWorking = new QIcon( pixWorking );
	mIconImperfect = new QIcon( pixImperfect );
	mIconNotWorking = new QIcon( pixNotWorking );
}

MachineModel::~MachineModel()
{
	delete mIconWorking;
	delete mIconImperfect;
	delete mIconNotWorking;
}

int MachineModel::columnCount( const QModelIndex& parent ) const
{
	Q_UNUSED( parent );
	return 1;
}

QVariant MachineModel::data( const QModelIndex& index, int role ) const
{
	if ( !index.isValid() )
	{
		return QVariant();
	}
	
	MachineItem* item = static_cast<MachineItem*>( index.internalPointer() );

	switch ( role )
	{
		case Qt::DecorationRole:
			return QIcon( item->icon() );
			break;
		case Qt::DisplayRole:
			return item->text();
			break;
		case Qt::ToolTipRole:
			return QString( "%1 - %2" ).arg( item->infos().data( MachineInfos::Manufacturer ) ).arg( item->text() );
			break;
		case Qt::SizeHintRole:
			return QSize( 0, 18 );
			break;
	}
	
	return QVariant();
}

Qt::ItemFlags MachineModel::flags( const QModelIndex& index ) const
{
	if ( !index.isValid() )
	{
		return 0;
	}

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant MachineModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
	{
		switch (section) {
			case 0:
				return tr( "Name" );
			/*
			case 1:
				return tr( "Attributes" );
			case 2:
				return tr( "Value" );
			*/
			default:
				return QVariant();
		}
	}

	return QVariant();
}

QModelIndex MachineModel::index( int row, int column, const QModelIndex& parent ) const
{
	if ( !hasIndex( row, column, parent ) )
	{
		return QModelIndex();
	}

	MachineItem* parentItem;

	if ( !parent.isValid() )
	{
		parentItem = rootItem();
	}
	else
	{
		parentItem = static_cast<MachineItem*>( parent.internalPointer() );
	}

	MachineItem* childItem = parentItem->child( row );
	
	if ( childItem )
	{
		return createIndex( row, column, childItem );
	}
	else
	{
		return QModelIndex();
	}
}

QModelIndex MachineModel::parent( const QModelIndex& child ) const
{
	if ( !child.isValid() )
	{
		return QModelIndex();
	}

	MachineItem* childItem = static_cast<MachineItem*>( child.internalPointer() );
	MachineItem* parentItem = childItem->parent();

	if ( !parentItem || parentItem == rootItem() )
	{
		return QModelIndex();
	}

	return createIndex( parentItem->row(), 0, parentItem );
}

int MachineModel::rowCount( const QModelIndex& parent ) const
{
	if ( parent.column() > 0 )
	{
		return 0;
	}

	MachineItem* parentItem;

	if ( !parent.isValid() )
	{
		parentItem = rootItem();
	}
	else
	{
		parentItem = static_cast<MachineItem*>( parent.internalPointer() );
	}

	return parentItem ? parentItem->count() : 0;
}

MachineItem* MachineModel::rootItem() const
{
	return mMachineItems.value( QLatin1String( "mess" ) );
}

MachineItemList MachineModel::rootItems() const
{
	MachineItem* root = rootItem();
	MachineItemList items;
	
	foreach ( MachineItem* item, mMachineItems )
	{
		if ( item->parent() == root )
		{
			items << item;
		}
	}
	
	MachineItem::sort( items );
	return items;
}

MachineItem* MachineModel::itemFromIndex( const QModelIndex& index ) const
{
	if ( index.isValid() )
	{
		return static_cast<MachineItem*>( index.internalPointer() );
	}
	
	return 0;
}

QModelIndex MachineModel::itemToIndex( MachineItem* item ) const
{
	MachineItem* root = rootItem();
	
	if ( item && item != root )
	{
		return createIndex( item->row(), 0, item );
	}
	
	return QModelIndex();
}

MachineItem* MachineModel::machineItem( const QString& name ) const
{
	return mMachineItems.value( name );
}

QModelIndex MachineModel::machineIndex( const QString& name ) const
{
	return itemToIndex( machineItem( name ) );
}

void MachineModel::setDocument( const QDomDocument& document )
{
	if ( mDocument != document )
	{
		clear( document );
	}
}

void MachineModel::setIconsPath( const QString& path )
{
	mIconsPath = path;
}

QString MachineModel::iconsPath() const
{
	return mIconsPath;
}

void MachineModel::createItems()
{
	QDomElement root = mDocument.documentElement();
	QDomNodeList nodes = root.childNodes();
	
	mMachineItems[ "mess" ] = new MachineItem( this, root );
	
	for ( int i = 0; i < nodes.count(); i++ )
	{
		MachineItem* item = new MachineItem( this, nodes.at( i ).toElement() );
		mMachineItems[ item->infos().data( MachineInfos::Name ) ] = item;
	}
}

void MachineModel::arrangeItems()
{
	foreach ( MachineItem* item, mMachineItems )
	{
		item->clear();
	}
	
	MachineItem* root = rootItem();
	
	foreach ( MachineItem* item, mMachineItems )
	{
		const QString cloneOf = item->infos().data( MachineInfos::CloneOf );
		
		if ( cloneOf.isEmpty() )
		{
			if ( item != root )
			{
				root->appendItem( item );
			}
		}
		else
		{
			mMachineItems[ cloneOf ]->appendItem( item );
		}
	}
}

void MachineModel::clear( const QDomDocument& document )
{
	qDeleteAll( mMachineItems );
	mMachineItems.clear();
	mDocument = document;
	createItems();
	arrangeItems();
	reset();
	emit ready();
}

QIcon MachineModel::icon( MachineModel::State state ) const
{
	switch ( state )
	{
		case MachineModel::Working:
			return *mIconWorking;
			break;
		case MachineModel::Imperfect:
			return *mIconImperfect;
			break;
		case MachineModel::NotWorking:
			return *mIconNotWorking;
			break;
	}
	
	return QIcon();
}

MachinesCount MachineModel::count( MachineItem* parent ) const
{
	MachinesCount mcount;
	MachineItem* root = rootItem();
	parent = parent ? parent : root;
	
	foreach ( MachineItem* item, parent->children() )
	{
		mcount.total++;
		
		if ( item->infos().data( MachineInfos::CloneOf ).isEmpty() )
		{
			mcount.unique++;
		}
		else
		{
			mcount.clones++;
		}
		
		mcount += count( item );
	}
	
	return mcount;
}
