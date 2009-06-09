#ifndef ROMFILTERMODEL_H
#define ROMFILTERMODEL_H

#include <QSortFilterProxyModel>
#include <QStringList>

class RomModel;

class RomFilterModel : public QSortFilterProxyModel
{
	Q_OBJECT
	
public:
	RomFilterModel( RomModel* parent = 0 );
	virtual ~RomFilterModel();
	
	QStringList filters() const;
	void setFilters( const QStringList& filters );
	
protected:
	RomModel* mModel;
	QStringList mFilters;
	
	virtual bool filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const;
};

#endif // ROMFILTERMODEL_H
