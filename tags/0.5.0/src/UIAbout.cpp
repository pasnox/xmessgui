#include "UIAbout.h"
#include "main.h"

#include <QDesktopServices>
#include <QDebug>

UIAbout::UIAbout( QWidget* parent )
	: QDialog( parent )
{
	setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose );
	setWindowTitle( tr( "About - %1" ).arg( PACKAGE_NAME ) );
	
	QStringList authors = QString( PACKAGE_AUTHORS ).split( "|" ).replaceInStrings( QRegExp( "^(.*)$" ), "<li>\\1</li>" );
	authors.replaceInStrings( QRegExp( "([\\w]+@[\\w\\_-]+\\.[\\w\\_-]+)" ), "<a href=\"mailto:\\1\">\\1</a>" );
	
	if ( !authors.isEmpty() )
	{
		authors.prepend( "<ul>" );
		authors.append( "</ul>" );
	}
	
	
	lInformations->setText( QString( "<b>%1 - v%2</b><br />%3<br /><a href=\"%4\">%4</a>" ).arg( PACKAGE_NAME ).arg( PACKAGE_VERSION ).arg( PACKAGE_COMMENT ).arg( PACKAGE_HOMEPAGE ) );
	lLicense->setToolTip( tr( "%1 license" ).arg( PACKAGE_LICENSE ) );
	tbAuthors->setHtml( authors.join( "\n" ).prepend( tr( "Authors:" ) ) );
	
	lSDLMess->installEventFilter( this );
	lLicense->installEventFilter( this );
	lMonkeyStudio->installEventFilter( this );
}

UIAbout::~UIAbout()
{
}

bool UIAbout::eventFilter( QObject* object, QEvent* event )
{
	if ( event->type() == QEvent::MouseButtonRelease )
	{
		if ( object == lSDLMess )
		{
			QDesktopServices::openUrl( QUrl( "http://rbelmont.mameworld.info/?page_id=163" ) );
		}
		else if ( object == lLicense )
		{
			QDesktopServices::openUrl( QUrl( "http://www.gnu.org/copyleft/gpl.html" ) );
		}
		else if ( object == lMonkeyStudio )
		{
			QDesktopServices::openUrl( QUrl( "http://monkeystudio.org" ) );
		}
	}
	
	return QDialog::eventFilter( object, event );
}
