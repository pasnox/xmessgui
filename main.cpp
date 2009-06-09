#include <QApplication>

#include "UIMain.h"

int main( int argc, char** argv )
{
	// create application
	QApplication app( argc, argv );

	// init application
	app.setOrganizationDomain( "xmessgui.sf.net" );
	app.setOrganizationName( "xMessGui" );
	app.setApplicationName( "xMessGui" );

	UIMain w;
	w.showMaximized();

	// connection
	QObject::connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );

	// start application
	return app.exec();
}
