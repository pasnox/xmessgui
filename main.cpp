/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : main.cpp
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include <QApplication>

#include "UIMain.h"

int main( int argc, char** argv )
{
	// create application
	QApplication app( argc, argv );
	app.setQuitOnLastWindowClosed( false );

	// init application
	app.setOrganizationDomain( "xmessgui.sf.net" );
	app.setOrganizationName( "xMessGui" );
	app.setApplicationName( "xMessGui" );

	UIMain w;
	w.showMaximized();

	// start application
	return app.exec();
}
