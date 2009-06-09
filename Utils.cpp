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