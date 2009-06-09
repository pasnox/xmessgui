#include "MachineFilterModel.h"
#include "MachineModel.h"
#include "MachineItem.h"

#include <QDebug>

MachineFilterModel::MachineFilterModel( MachineModel* parent )
	: QSortFilterProxyModel( parent )
{
	Q_ASSERT( parent );
	
	setFilterCaseSensitivity( Qt::CaseInsensitive );
	setSortCaseSensitivity( Qt::CaseInsensitive );
	
	mModel = parent;
	setSourceModel( parent );
	
	connect( mModel, SIGNAL( ready() ), this, SLOT( machineModel_ready() ) );
}

MachineFilterModel::~MachineFilterModel()
{
}

bool MachineFilterModel::filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const
{
	const QModelIndex machineIndex = mModel->index( source_row, 0, source_parent );
	const MachineItem* machine = mModel->itemFromIndex( machineIndex );
	
	if ( !machine->text().contains( filterRegExp() ) && !machine->infos().data( MachineInfos::Manufacturer ).contains( filterRegExp() ) )
	{
		foreach ( const MachineItem* item, machine->children() )
		{
			if ( filterAcceptsRow( item->row(), machineIndex ) )
			{
				return true;
			}
		}
		
		return false;
	}
	
	return true;
}

void MachineFilterModel::machineModel_ready()
{
	sort( 0, Qt::AscendingOrder );
}
