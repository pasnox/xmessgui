/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : RomFilterModel.cpp
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
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
