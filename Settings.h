#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMap>
#include <QString>

class Settings
{
public:
	Settings();
	virtual ~Settings();
	
	bool load();
	bool save();
	
	bool isInitialized() const;
	
	QString binary() const;
	void setBinary( const QString& binary );
	
	QString biosPath() const;
	void setBiosPath( const QString& binary );
	
	QMap<QString, QString> romsPaths() const;
	QString romsPath( const QString& name, const QString& cloneName = QString::null ) const;
	void setRomsPaths( const QMap<QString, QString>& paths );
	void setRomsPath( const QString& name, const QString& path );
	
	QString currentMachine() const;
	void setCurrentMachine( const QString& name );
	
protected:
	QString mBinary;
	QString mBiosPath;
	QMap<QString, QString> mRomsPaths;
	QString mCurrentMachine;
};

#endif // SETTINGS_H