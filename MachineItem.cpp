#include "MachineItem.h"
#include "MachineModel.h"

#include <QDebug>

MachineItem::MachineItem( MachineModel* model, const QDomElement& element )
{
	Q_ASSERT( model );
	
	mModel = model;
	mInfos = MachineInfos( element );
	mParent = 0;
}

MachineItem::~MachineItem()
{
}

MachineItem* MachineItem::parent() const
{
	return mParent;
}

void MachineItem::setParent( MachineItem* parent )
{
	mParent = parent;
}

MachineItemList MachineItem::children() const
{
	return mChildren;
}

MachineItem* MachineItem::child( int row ) const
{
	return mChildren.value( row );
}

int MachineItem::count() const
{
	return mChildren.count();
}

int MachineItem::row() const
{
	return mParent ? mParent->mChildren.indexOf( const_cast<MachineItem*>( this ) ) : -1;
}

void MachineItem::appendItem( MachineItem* item )
{
	if ( !mChildren.contains( item ) )
	{
		item->setParent( this );
		mChildren << item;
	}
}

void MachineItem::removeItem( MachineItem* item )
{
	mChildren.removeAll( item );
}

void MachineItem::clear()
{
	mChildren.clear();
}

MachineModel* MachineItem::model() const
{
	return mModel;
}

QString MachineItem::text() const
{
	return mInfos.data( MachineInfos::Description );
}

QPixmap MachineItem::icon() const
{
	const QString name = mInfos.data( MachineInfos::Name );
	QPixmap pixmap = QPixmap( mModel->iconsPath().append( QString( "/%1/%1.png" ).arg( name ) ) );
	
	if ( pixmap.isNull() && parent() )
	{
		pixmap = parent()->icon();
	}
	
	return pixmap;
}

QBrush MachineItem::background() const
{
	const QString status = mInfos.mDriver.data( iDriver::Status );
	const int lighter = 180;
	QBrush brush;
	
	if ( status == "preliminary" )
	{
		brush = QColor( Qt::red ).lighter( lighter );
	}
	else if ( status == "imperfect" )
	{
		brush = QColor( Qt::blue ).lighter( lighter );
	}
	else if ( status == "good" )
	{
		brush = QColor( Qt::green ).lighter( lighter );
	}
	
	return brush;
}

const MachineInfos& MachineItem::infos() const
{
	return mInfos;
}

bool MachineItem::lessThan( MachineItem* left, MachineItem* right )
{
	return left->text().toLower() < right->text().toLower();
}

void MachineItem::sort( MachineItemList& items )
{
	qSort( items.begin(), items.end(), lessThan );
}
