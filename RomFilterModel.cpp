#include "RomFilterModel.h"
#include "RomModel.h"

#include <QDir>
#include <QDebug>

RomFilterModel::RomFilterModel( RomModel* parent )
	: QSortFilterProxyModel( parent )
{
	Q_ASSERT( parent );
	
	mModel = parent;
	setSourceModel( parent );
	
	connect( mModel, SIGNAL( ready() ), this, SLOT( romModel_ready() ) );
}

RomFilterModel::~RomFilterModel()
{
}

void RomFilterModel::romModel_ready()
{
	sort( 0, Qt::AscendingOrder );
	emit ready();
}
