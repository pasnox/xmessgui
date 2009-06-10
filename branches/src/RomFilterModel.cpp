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
}

RomFilterModel::~RomFilterModel()
{
}
