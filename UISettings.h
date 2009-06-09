#ifndef UISETTINGS_H
#define UISETTINGS_H

#include "ui_UISettings.h"
#include "MachineModel.h"

class Settings;

class UISettings : public QDialog, public Ui::UISettings
{
		Q_OBJECT

public:
	UISettings( Settings* settings, const MachineItemList& machines, QWidget* parent = 0 );
	virtual ~UISettings();
	
protected:
	Settings* mSettings;
	MachineItemList mMachines;
	QMap<QString, QString> mRomsPaths;
	
	void initSettings();
	void restoreDefaults();
	
	QString getOpenFileName( const QString& text, const QString& fileName = QString::null, const QString& filter = QString::null );
	QString getExistingDirectory( const QString& text, const QString& path = QString::null );

protected slots:
	void on_tbBinaryFile_clicked();
	void on_tbBiosPath_clicked();
	void on_cbRomsPath_currentIndexChanged( int index );
	void on_tbRomsPathSet_clicked();
	void on_tbRomsPath_clicked();
	void on_dbbButtons_clicked( QAbstractButton* button );
	void accept();
};

#endif // UISETTINGS_H
