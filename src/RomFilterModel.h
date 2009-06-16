/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : RomFilterModel.h
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
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
