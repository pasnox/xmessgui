/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : MachineFilterModel.h
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
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

signals:
	void ready();
};

#endif // MACHINEFILTERMODEL_H
