#include "ProcessQuery.h"
#include "Settings.h"
#include "MachineItem.h"

ProcessQuery::ProcessQuery( Settings* settings, QObject* parent )
	: QProcess( parent )
{
	Q_ASSERT( settings );
	mSettings = settings;
	
	setObjectName( "processQuery" );
	setReadChannelMode( QProcess::MergedChannels );
	mCurrentTask = ProcessQuery::IDLE;
	
	connect( this, SIGNAL( error( QProcess::ProcessError ) ), this, SLOT( _q_error( QProcess::ProcessError ) ) );
	connect( this, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( _q_finished( int, QProcess::ExitStatus ) ) );
}

ProcessQuery::~ProcessQuery()
{
}

void ProcessQuery::startRom( MachineItem* machine, const QString& filePath )
{
	mMachineRomPair = qMakePair( machine, filePath );
	addTask( ProcessQuery::StartRom );
}

bool ProcessQuery::startNextTask()
{
	if ( mTasks.isEmpty() )
	{
		return false;
	}
	
	mCurrentTask = mTasks.dequeue();
	QStringList args;
	
	switch ( mCurrentTask )
	{
		case ProcessQuery::StartRom:
			args << mMachineRomPair.first->infos().name()
				<< "-skip_gameinfo"
				<< "-skip_warnings"
				<< "-cheat"
				<< "-multithreading"
				//<< "-sdlvideofps"
				<< "-keepaspect"
				<< "-waitvsync"
				<< "-unevenstretch"
				<< "-video" << "opengl" // soft or opengl
				//<< "-scalemode" << "yuy2x2" // none, async, yv12, yuy2, yv12x2, yuy2x2 (-video soft only)
				<< "-rompath" << mSettings->biosPath()
				<< "-cart" << mMachineRomPair.second;
			break;
		case ProcessQuery::ListXml:
			args << "-listxml";
			break;
		case ProcessQuery::IDLE:
			return false;
			break;
	}
	
	emit log( tr( "Running command: %1 %2" ).arg( mSettings->binary() ).arg( "\"" +args.join( "\" \"" ) +"\"" ) );
	start( mSettings->binary(), args );
	return true;
}

bool ProcessQuery::addTask( ProcessQuery::Task task )
{
	if ( mTasks.contains( task ) )
	{
		return false;
	}
	
	mTasks.enqueue( task );
	
	if ( state() == QProcess::NotRunning )
	{
		startNextTask();
	}
	
	return true;
}

void ProcessQuery::handleNormalExit()
{
	switch ( mCurrentTask )
	{
		case ProcessQuery::StartRom:
			break;
		case ProcessQuery::ListXml:
		{
			QDomDocument document;
			QByteArray datas = readAll();
			QString errorMsg;
			int errorLine;
			int errorColumn;
			bool ok = document.setContent( datas, &errorMsg, &errorLine, &errorColumn );
			
			emit listXmlFinished( document, !ok, errorMsg, QPoint( errorColumn, errorLine ) );
			break;
		}
		case ProcessQuery::IDLE:
			break;
	}
}

void ProcessQuery::_q_error( QProcess::ProcessError err )
{
	emit error( mCurrentTask, err );
}

void ProcessQuery::_q_finished( int exitCode, QProcess::ExitStatus exitStatus )
{
	Q_UNUSED( exitCode );
	
	switch ( exitStatus )
	{
		case QProcess::NormalExit:
			handleNormalExit();
			break;
		case QProcess::CrashExit:
			break;
	}
	
	startNextTask();
}

void ProcessQuery::listXml()
{
	addTask( ProcessQuery::ListXml );
}
