#ifndef PROCESSQUERY_H
#define PROCESSQUERY_H

#include <QProcess>
#include <QQueue>
#include <QDomDocument>
#include <QPoint>
#include <QPair>

class MachineItem;
class Settings;

typedef QPair<MachineItem*, QString> MachineRomPair;

class ProcessQuery : public QProcess
{
	Q_OBJECT
	
public:
	enum Task
	{
		IDLE,
		StartMachine,
		StartMachineRom,
		ListXml,
		VerifyRoms
	};
	
	ProcessQuery( Settings* settings, QObject* parent = 0 );
	virtual ~ProcessQuery();
	
	void startMachine( MachineItem* machine );
	void startMachineRom( MachineItem* machine, const QString& filePath );
	
public slots:
	void listXml();
	void verifyRoms();

protected:
	Settings* mSettings;
	QQueue<ProcessQuery::Task> mTasks;
	ProcessQuery::Task mCurrentTask;
	MachineRomPair mMachineRomPair;
	
	bool startNextTask();
	bool addTask( ProcessQuery::Task task );
	void handleNormalExit();
	
protected slots:
	void _q_started();
	void _q_error( QProcess::ProcessError error );
	void _q_finished( int exitCode, QProcess::ExitStatus exitStatus );

signals:
	void log( const QString& message );
	void started( ProcessQuery::Task task );
	void error( ProcessQuery::Task task, QProcess::ProcessError error );
	void listXmlFinished( const QDomDocument& document, bool error, const QString& errorMsg, const QPoint& errorPosition );
	void verifyRomsFinished( const QString& buffer );
};

#endif // PROCESSQUERY_H
