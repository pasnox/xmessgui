/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : UIMain.h
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef UIMAIN_H
#define UIMAIN_H

#include "ui_UIMain.h"
#include "ProcessQuery.h"

class Settings;
class MachineModel;
class MachineItem;
class MachineFilterModel;
class RomModel;
class RomFilterModel;

class UIMain : public QMainWindow, public Ui::UIMain
{
	Q_OBJECT

public:
	UIMain( QWidget* parent = 0 );
	virtual ~UIMain();
	
public slots:
	void appendLog( const QString& message );

protected:
	Settings* mSettings;
	ProcessQuery* mProcessQuery;
	MachineModel* mMachineModel;
	MachineFilterModel* mMachineFilterModel;
	RomModel* mRomModel;
	RomFilterModel* mRomFilterModel;
	
	void closeEvent( QCloseEvent* event );

protected slots:
	void reloadSettings();
	void machineFilterModel_ready();
	void romFilterModel_ready();
	void on_aSettings_triggered();
	void on_aVerifyRoms_triggered();
	void on_aQuit_triggered();
	void on_aStartMachine_triggered();
	void on_aStartMachineRom_triggered();
	void on_aAbout_triggered();
	void on_tvMachines_activated( const QModelIndex& index );
	void on_seRomsFilter_searchChanged( const QString& text );
	void on_tvRoms_activated( const QModelIndex& index );
	void on_processQuery_started( ProcessQuery::Task task );
	void on_processQuery_error( ProcessQuery::Task task, QProcess::ProcessError error );
	void on_processQuery_finished( int exitCode, QProcess::ExitStatus exitStatus );
	void on_processQuery_listXmlFinished( const QDomDocument& document, bool error, const QString& errorMsg, const QPoint& errorPosition );
	void on_processQuery_verifyRomsFinished( const QString& buffer );
};

#endif // UIMAIN_H
