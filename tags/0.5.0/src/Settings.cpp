/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : Settings.cpp
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
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
	mBios = settings.value( "Bios", QString( "%1/.mess/bios" ).arg( QDir::homePath() ) ).toString();
	mResources = settings.value( "Resources", QString( "%1/.mess/resources" ).arg( QDir::homePath() ) ).toString();
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
	
	// performance
	settings.beginGroup( "Performance" );
	mMultithreading = settings.value( "Multithreading", false ).toBool();
	mSDLFPS = settings.value( "SDLFPS", false ).toBool();
	settings.endGroup();
	
	// video
	settings.beginGroup( "Video" );
	mVideoMode = settings.value( "VideoMode", "opengl" ).toString();
	mScaleMode = settings.value( "ScaleMode", "none" ).toString();
	mFullScreen = settings.value( "FullScreen", false ).toBool();
	mMaximize = settings.value( "Maximize", false ).toBool();
	mKeepAspectRatio = settings.value( "KeepAspectRatio", false ).toBool();
	mAllowDoubleStretchFactors = settings.value( "AllowDoubleStretchFactors", false ).toBool();
	mWaitVBLANK = settings.value( "WaitVBLANK", false ).toBool();
	settings.endGroup();
	
	// misc
	settings.beginGroup( "Misc" );
	mSkipGameInformations = settings.value( "SkipGameInformations", false ).toBool();
	mSkipWarnings = settings.value( "SkipWarnings", false ).toBool();
	mCheat = settings.value( "Cheat", false ).toBool();
	settings.endGroup();
	
	// states
	settings.beginGroup( "States" );
	mAutoSave = settings.value( "AutoSave", false ).toBool();
	settings.endGroup();
	
	return true;
}

bool Settings::save()
{
	QSettings settings;
	
	settings.beginGroup( qApp->applicationName() );
	settings.setValue( "Binary", mBinary );
	settings.setValue( "Bios", mBios );
	settings.setValue( "Resources", mResources );
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
	
	// performance
	settings.beginGroup( "Performance" );
	settings.setValue( "Multithreading", mMultithreading );
	settings.setValue( "SDLFPS", mSDLFPS );
	settings.endGroup();
	
	// video
	settings.beginGroup( "Video" );
	settings.setValue( "VideoMode", mVideoMode );
	settings.setValue( "ScaleMode", mScaleMode );
	settings.setValue( "FullScreen", mFullScreen );
	settings.setValue( "Maximize", mMaximize );
	settings.setValue( "KeepAspectRatio", mKeepAspectRatio );
	settings.setValue( "AllowDoubleStretchFactors", mAllowDoubleStretchFactors );
	settings.setValue( "WaitVBLANK", mWaitVBLANK );
	settings.endGroup();
	
	// misc
	settings.beginGroup( "Misc" );
	settings.setValue( "SkipGameInformations", mSkipGameInformations );
	settings.setValue( "SkipWarnings", mSkipWarnings );
	settings.setValue( "Cheat", mCheat );
	settings.endGroup();
	
	// misc
	settings.beginGroup( "States" );
	settings.setValue( "AutoSave", mAutoSave );
	settings.endGroup();
	
	return settings.isWritable();
}

bool Settings::isInitialized() const
{
	QSettings settings;
	
	return !settings.allKeys().isEmpty();
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

QString Settings::stringValue( Settings::StringType type ) const
{
	switch ( type )
	{
		case Settings::Binary:
			return mBinary;
			break;
		case Settings::Bios:
			return mBios;
			break;
		case Settings::Resources:
			return mResources;
			break;
		case Settings::CurrentMachine:
			return mCurrentMachine;
			break;
		case Settings::MachineFilter:
			return mMachineFilter;
			break;
		case Settings::RomsFilter:
			return mRomsFilter;
			break;
		case Settings::VideoMode:
			return mVideoMode;
			break;
		case Settings::ScaleMode:
			return mScaleMode;
			break;
	}
	
	Q_ASSERT( 0 );
	return QString::null;
}

void Settings::setStringValue( Settings::StringType type, const QString& value )
{

	switch ( type )
	{
		case Settings::Binary:
			mBinary = value;
			break;
		case Settings::Bios:
			mBios = value;
			break;
		case Settings::Resources:
			mResources = value;
			break;
		case Settings::CurrentMachine:
			mCurrentMachine = value;
			break;
		case Settings::MachineFilter:
			mMachineFilter = value;
			break;
		case Settings::RomsFilter:
			mRomsFilter = value;
			break;
		case Settings::VideoMode:
			mVideoMode = value;
			break;
		case Settings::ScaleMode:
			mScaleMode = value;
			break;
		default:
			Q_ASSERT( 0 );
			break;
	}
}

bool Settings::boolValue( Settings::BoolType type ) const
{
	switch ( type )
	{
		case Settings::Multithreading:
			return mMultithreading;
			break;
		case Settings::SDLFPS:
			return mSDLFPS;
			break;
		case Settings::FullScreen:
			return mFullScreen;
			break;
		case Settings::Maximize:
			return mMaximize;
			break;
		case Settings::KeepAspectRatio:
			return mKeepAspectRatio;
			break;
		case Settings::AllowDoubleStretchFactors:
			return mAllowDoubleStretchFactors;
			break;
		case Settings::WaitVBLANK:
			return mWaitVBLANK;
			break;
		case Settings::SkipGameInformations:
			return mSkipGameInformations;
			break;
		case Settings::SkipWarnings:
			return mSkipWarnings;
			break;
		case Settings::Cheat:
			return mCheat;
			break;
		case Settings::AutoSave:
			return mAutoSave;
			break;
	}
	
	Q_ASSERT( 0 );
	return false;
}

void Settings::setBoolValue( Settings::BoolType type, bool value )
{
	switch ( type )
	{
		case Settings::Multithreading:
			mMultithreading = value;
			break;
		case Settings::SDLFPS:
			mSDLFPS = value;
			break;
		case Settings::FullScreen:
			mFullScreen = value;
			break;
		case Settings::Maximize:
			mMaximize = value;
			break;
		case Settings::KeepAspectRatio:
			mKeepAspectRatio = value;
			break;
		case Settings::AllowDoubleStretchFactors:
			mAllowDoubleStretchFactors = value;
			break;
		case Settings::WaitVBLANK:
			mWaitVBLANK = value;
			break;
		case Settings::SkipGameInformations:
			mSkipGameInformations = value;
			break;
		case Settings::SkipWarnings:
			mSkipWarnings = value;
			break;
		case Settings::Cheat:
			mCheat = value;
			break;
		case Settings::AutoSave:
			mAutoSave = value;
			break;
		default:
			Q_ASSERT( 0 );
			break;
	}
}
