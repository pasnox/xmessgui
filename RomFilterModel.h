#ifndef ROMFILTERMODEL_H
#define ROMFILTERMODEL_H

#include <QSortFilterProxyModel>

class RomModel;

class RomFilterModel : public QSortFilterProxyModel
{
	Q_OBJECT
	
public:
	RomFilterModel( RomModel* parent = 0 );
	virtual ~RomFilterModel();
	
protected:
	RomModel* mModel;

protected slots:
	void romModel_ready();

signals:
	void ready();
};

#endif // ROMFILTERMODEL_H
