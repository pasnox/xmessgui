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
