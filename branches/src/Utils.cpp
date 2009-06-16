/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : Utils.cpp
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "Utils.h"

#include <QObject>

QString Utils::fileSizeAdaptString( double nb )
{
	return nb >= 100 ? QString::number( nb, 'f', 0 ) : QString::number( nb, 'g', 3 );
}

QString Utils::fileSizeToString( double nb )
{
	if ( nb < 1024 )
	{
		return QString::number( nb ) +QObject::tr( "B"  );
	}
	
	if ( ( nb = nb / 1024 ) < 1024 )
	{
		return fileSizeAdaptString( nb ) +QObject::tr( "KB" );
	}
	
	if ( ( nb = nb / 1024) < 1024 )
	{
		return fileSizeAdaptString( nb ) +QObject::tr( "MB" );
	}
	
	if ( ( nb = nb / 1024) < 1024 )
	{
		return fileSizeAdaptString( nb ) +QObject::tr( "GB" );
	}
	
	if ( ( nb = nb / 1024) < 1024 )
	{
		return fileSizeAdaptString( nb ) +QObject::tr( "TB" );
	}
	
	if ( ( nb = nb / 1024) < 1024 )
	{
		return fileSizeAdaptString( nb ) +QObject::tr( "PB" );
	}
	
	return QObject::tr( "Too big" );
}
