#include "RomFilterModel.h"
#include "RomModel.h"

#include <QDir>
#include <QDebug>

RomFilterModel::RomFilterModel( RomModel* parent )
	: QSortFilterProxyModel( parent )
{
	Q_ASSERT( parent );
	
	setFilterCaseSensitivity( Qt::CaseInsensitive );
	//setSortCaseSensitivity( Qt::CaseInsensitive );
	setDynamicSortFilter( true );
	
	mModel = parent;
	setSourceModel( parent );
}

RomFilterModel::~RomFilterModel()
{
}

QStringList RomFilterModel::filters() const
{
	return mFilters;
}

void RomFilterModel::setFilters( const QStringList& filters )
{
	mFilters = filters;
	invalidateFilter();
}

bool RomFilterModel::filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const
{
	const QModelIndex index = mModel->index( source_row, 1, source_parent );
	const QString fileName = index.data().toString();
	
	const bool match = mFilters.isEmpty() || QDir::match( mFilters, fileName );
	const bool contains = fileName.contains( filterRegExp() );
	const bool result = match && contains;
	
	return result;
}
