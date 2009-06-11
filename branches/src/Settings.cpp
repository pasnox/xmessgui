#include "Settings.h"

#include <QSettings>
#include <QApplication>
#include <QDir>

Settings::Settings()
{
	load();
}

Settings::~Settings()
{
	save();
}

bool Settings::load()
{
	QSettings settings;
	
	settings.beginGroup( qApp->applicationName() );
	mBinary = settings.value( "Binary", "sdlmess" ).toString();
	mBiosPath = settings.value( "Bios", QString( "%1/.%2/bios" ).arg( QDir::homePath() ).arg( qApp->applicationName() ) ).toString();
	mCurrentMachine = settings.value( "CurrentMachine" ).toString();
	mMachineFilter = settings.value( "MachineFilter" ).toString();
	mRomsFilter = settings.value( "RomsFilter" ).toString();
	settings.endGroup();
	
	settings.beginGroup( "Roms" );
	mRomsPaths.clear();
	foreach ( const QString& name, settings.childKeys() )
	{
		mRomsPaths[ name ] = settings.value( name ).toString();
	}
	settings.endGroup();
	
	return true;
}

bool Settings::save()
{
	QSettings settings;
	
	settings.beginGroup( qApp->applicationName() );
	settings.setValue( "Binary", mBinary );
	settings.setValue( "Bios", mBiosPath );
	settings.setValue( "CurrentMachine", mCurrentMachine );
	settings.setValue( "MachineFilter", mMachineFilter );
	settings.setValue( "RomsFilter", mRomsFilter );
	settings.endGroup();
	
	settings.beginGroup( "Roms" );
	settings.remove( QString::null );
	foreach ( const QString& name, mRomsPaths.keys() )
	{
		settings.setValue( name, mRomsPaths[ name ] );
	}
	settings.endGroup();
	
	return settings.isWritable();
}

bool Settings::isInitialized() const
{
	QSettings settings;
	
	return !settings.allKeys().isEmpty();
}

QString Settings::binary() const
{
	return mBinary;
}

void Settings::setBinary( const QString& binary )
{
	mBinary = binary;
}

QString Settings::biosPath() const
{
	return mBiosPath;
}

void Settings::setBiosPath( const QString& path )
{
	mBiosPath = path;
}

QMap<QString, QString> Settings::romsPaths() const
{
	return mRomsPaths;
}

QString Settings::romsPath( const QString& name, const QString& cloneName ) const
{
	QString path = mRomsPaths.value( name );
	
	if ( path.isEmpty() )
	{
		path = mRomsPaths.value( cloneName );
	}
	
	return path;
}

void Settings::setRomsPaths( const QMap<QString, QString>& paths )
{
	mRomsPaths = paths;
}

void Settings::setRomsPath( const QString& name, const QString& path )
{
	mRomsPaths[ name ] = path;
}

QString Settings::currentMachine() const
{
	return mCurrentMachine;
}

void Settings::setCurrentMachine( const QString& name )
{
	mCurrentMachine = name;
}

QString Settings::machineFilter() const
{
	return mMachineFilter;
}

void Settings::setMachineFilter( const QString& filter )
{
	mMachineFilter = filter;
}

QString Settings::romsFilter() const
{
	return mRomsFilter;
}

void Settings::setRomsFilter( const QString& filter )
{
	mRomsFilter = filter;
}
