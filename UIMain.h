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
	RomModel* mRomsModel;
	RomFilterModel* mRomFilterModel;

protected slots:
	void reloadSettings();
	void machineModel_ready();
	void romsModel_ready();
	void on_aSettings_triggered();
	void on_aQuit_triggered();
	void on_tvMachines_activated( const QModelIndex& index );
	void on_seRomsFilter_searchChanged( const QString& text );
	void on_tvRoms_activated( const QModelIndex& index );
	void on_processQuery_error( ProcessQuery::Task task, QProcess::ProcessError error );
	void on_processQuery_finished( int exitCode, QProcess::ExitStatus exitStatus );
	void on_processQuery_listXmlFinished( const QDomDocument& document, bool error, const QString& errorMsg, const QPoint& errorPosition );
};

#endif // UIMAIN_H
