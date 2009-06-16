/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : Settings.h
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMap>
#include <QString>

class Settings
{
public:
	enum StringType
	{
		Binary,
		Bios,
		Resources,
		CurrentMachine,
		MachineFilter,
		RomsFilter,
		VideoMode,
		ScaleMode
	};
	
	enum BoolType
	{
		Multithreading,
		SDLFPS,
		FullScreen,
		Maximize,
		KeepAspectRatio,
		AllowDoubleStretchFactors,
		WaitVBLANK,
		SkipGameInformations,
		SkipWarnings,
		Cheat,
		AutoSave
	};
	
	Settings();
	virtual ~Settings();
	
	bool load();
	bool save();
	
	bool isInitialized() const;
	
	QMap<QString, QString> romsPaths() const;
	QString romsPath( const QString& name, const QString& cloneName = QString::null ) const;
	void setRomsPaths( const QMap<QString, QString>& paths );
	void setRomsPath( const QString& name, const QString& path );
	
	QString stringValue( Settings::StringType type ) const;
	void setStringValue( Settings::StringType type, const QString& value );
	
	bool boolValue( Settings::BoolType type ) const;
	void setBoolValue( Settings::BoolType type, bool value );
	
protected:
	QString mBinary;
	QString mBios;
	QString mResources;
	QMap<QString, QString> mRomsPaths;
	QString mCurrentMachine;
	QString mMachineFilter;
	QString mRomsFilter;
	// performance
	bool mMultithreading;
	bool mSDLFPS;
	// video
	QString mVideoMode;
	QString mScaleMode;
	bool mFullScreen;
	bool mMaximize;
	bool mKeepAspectRatio;
	bool mAllowDoubleStretchFactors;
	bool mWaitVBLANK;
	bool mSkipGameInformations;
	bool mSkipWarnings;
	bool mCheat;
	bool mAutoSave;
};

#endif // SETTINGS_H
