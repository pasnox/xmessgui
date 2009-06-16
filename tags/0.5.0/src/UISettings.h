/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : UISettings.h
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef UISETTINGS_H
#define UISETTINGS_H

#include "ui_UISettings.h"
#include "MachineModel.h"

class Settings;
class MachineFilterModel;

class UISettings : public QDialog, public Ui::UISettings
{
	Q_OBJECT

public:
	UISettings( Settings* settings, MachineModel* machineModel, QWidget* parent = 0 );
	virtual ~UISettings();
	
protected:
	Settings* mSettings;
	MachineModel* mMachineModel;
	MachineFilterModel* mMachineFilterModel;
	QMap<QString, QString> mRomsPaths;
	
	void initSettings();
	void restoreDefaults();
	
	QString getOpenFileName( const QString& text, const QString& fileName = QString::null, const QString& filter = QString::null );
	QString getExistingDirectory( const QString& text, const QString& path = QString::null );

protected slots:
	void on_tbBinaryFile_clicked();
	void on_tbBiosPath_clicked();
	void on_tbResourcesPath_clicked();
	void on_tvRomsPath_activated( const QModelIndex &index );
	void on_tbRomsPathSet_clicked();
	void on_tbRomsPath_clicked();
	void on_cbVideoMode_currentIndexChanged( const QString& text );
	void on_dbbButtons_clicked( QAbstractButton* button );
	void accept();
};

#endif // UISETTINGS_H
