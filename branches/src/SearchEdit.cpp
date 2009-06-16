/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : SearchEdit.cpp
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "SearchEdit.h"

#include <QToolButton>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QTimer>

#define SEARCH_TIMEOUT 1000

SearchEdit::SearchEdit( QWidget* parent, const QString& promptText )
	: QLineEdit( parent )
{
	mShowPrompt = false;
	mTimer = new QTimer( this );
	mTimer->setInterval( SEARCH_TIMEOUT );
	mTimer->setSingleShot( true );
	
	mOptionsButton = new QToolButton( this );
	mOptionsButton->setIcon( QIcon( ":/icons/search.png" ) );
	mOptionsButton->setToolTip( tr( "Search Options" ) );
	mOptionsButton->setStyleSheet( "QToolButton { border: none; padding: 0px; } QToolButton::menu-indicator { right: -2px; bottom: -2px; }" );
	mOptionsButton->setCursor( Qt::ArrowCursor );
	mOptionsButton->setFocusPolicy( Qt::NoFocus );
	mOptionsButton->setPopupMode( QToolButton::InstantPopup );

	mClearButton = new QToolButton( this );
	mClearButton->setIcon( QIcon( ":/icons/clear.png" )  );
	mClearButton->setToolTip( tr( "Clear" ) );
	mClearButton->setStyleSheet( "QToolButton { border: none; padding: 0px; }" );
	mClearButton->setCursor( Qt::ArrowCursor );
	mClearButton->setFocusPolicy( Qt::NoFocus );
	mClearButton->setVisible( false );

	QSize buttonSize = mOptionsButton->sizeHint();
	int frameWidth = style()->pixelMetric( QStyle::PM_DefaultFrameWidth );

	int padding = buttonSize.width() +frameWidth +1;
	setStyleSheet( QString( "QLineEdit { padding-left: %1px; padding-right: %1px; } " ).arg( padding ) );

	setMinimumHeight( qMax( minimumSizeHint().height(), buttonSize.height() +2 *frameWidth ) );
	setSizePolicy( QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed ) );

	showPrompt( true );
	setPromptText( promptText );
	
	connect( mClearButton, SIGNAL( clicked() ), this, SLOT( clear() ) );
	connect( this, SIGNAL( textChanged( const QString& ) ), this, SLOT( updateCloseButton( const QString& ) ) );
	connect( mTimer, SIGNAL( timeout() ), this, SLOT( timer_timeout() ) );
}

QSize SearchEdit::sizeHint() const
{
	return QSize( 300, 20 );
}

void SearchEdit::setMenu( QMenu* menu )
{
	mOptionsButton->setMenu( menu );
}

void SearchEdit::resizeEvent( QResizeEvent* e )
{
	QLineEdit::resizeEvent( e );

	QSize buttonSize = mOptionsButton->sizeHint();
	int frameWidth = style()->pixelMetric( QStyle::PM_DefaultFrameWidth );

	int y = ( rect().bottom() +1 -buttonSize.height() ) /2;

	mOptionsButton->move( frameWidth, y );
	mClearButton->move( rect().right() -frameWidth -buttonSize.width(), y );
}

void SearchEdit::focusInEvent( QFocusEvent* e )
{
	QLineEdit::focusInEvent( e );

	if ( mShowPrompt )
	{
		showPrompt( false );
	}
}

void SearchEdit::focusOutEvent( QFocusEvent* e )
{
	QLineEdit::focusOutEvent( e );

	if ( text().isEmpty() )
	{
		showPrompt( true );
	}
}

void SearchEdit::paintEvent( QPaintEvent* e )
{
	QLineEdit::paintEvent( e );

	if ( mShowPrompt && !mTextPrompt.isEmpty() && text().isEmpty() )
	{
		QPainter painter( this );

		painter.setPen( palette().color( QPalette::Disabled, QPalette::Text ) );

		QStyleOption option;
		option.initFrom( this );
		QRect rect = style()->subElementRect( QStyle::SE_LineEditContents, &option, this );

		painter.setClipRect( rect );

		int x = rect.x() +2;
		int y = rect.y() +( rect.height() -fontMetrics().height() +1 ) /2;

		painter.drawText( x, y +fontMetrics().ascent(), mTextPrompt );
	}
}

void SearchEdit::showPrompt( bool show )
{
	mShowPrompt = show;

	update();
}

void SearchEdit::setPromptText( const QString& text )
{
	mTextPrompt = text;

	if ( mShowPrompt )
	{
		update();
	}
}

void SearchEdit::updateCloseButton( const QString& text )
{
	mClearButton->setVisible( !text.isEmpty() );
	mTimer->start();
}

void SearchEdit::timer_timeout()
{
	emit searchChanged( text() );
}
