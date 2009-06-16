/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : MachineItem.h
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef MACHINEITEM_H
#define MACHINEITEM_H

#include <QDomElement>
#include <QIcon>
#include <QPixmap>
#include <QBrush>
#include <QList>

#include "MachineInfos.h"

class MachineModel;
typedef QList<class MachineItem*> MachineItemList;

class MachineItem
{
public:
	MachineItem( MachineModel* model, const QDomElement& element );
	virtual ~MachineItem();
	
	MachineItem* parent() const;
	void setParent( MachineItem* parent );
	
	MachineItemList children() const;
	MachineItem* child( int row ) const;
	int count() const;
	
	void appendItem( MachineItem* item );
	void removeItem( MachineItem* item );
	void clear();
	
	MachineModel* model() const;
	int row() const;
	
	QString text() const;
	QIcon icon() const;
	QPixmap pixmap() const;
	
	const MachineInfos& infos() const;
	
	static bool lessThan( MachineItem* left, MachineItem* right );
	static void sort( MachineItemList& items );
	
protected:
	MachineModel* mModel;
	MachineInfos mInfos;
	MachineItem* mParent;
	MachineItemList mChildren;
};

#endif // MACHINEITEM_H
