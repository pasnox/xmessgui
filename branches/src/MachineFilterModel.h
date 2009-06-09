#ifndef MACHINEFILTERMODEL_H
#define MACHINEFILTERMODEL_H

#include <QSortFilterProxyModel>

class MachineModel;

class MachineFilterModel : public QSortFilterProxyModel
{
	Q_OBJECT
	
public:
	MachineFilterModel( MachineModel* parent = 0 );
	virtual ~MachineFilterModel();
	
protected:
	MachineModel* mModel;
	
	virtual bool filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const;
	
protected slots:
	void machineModel_ready();
};

#endif // MACHINEFILTERMODEL_H
