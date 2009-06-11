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
			args << mMachineRomPair.first->infos().data( MachineInfos::Name )
				<< "-skip_gameinfo"
				<< "-skip_warnings"
				<< "-cheat";
			
			// performance
			if ( mSettings->boolValue( Settings::Multithreading ) )
			{
				args << "-multithreading";
			}
			
			if ( mSettings->boolValue( Settings::SDLFPS ) )
			{
				args << "-sdlvideofps";
			}
			
			// video
			args << "-video";
			args << mSettings->stringValue( Settings::VideoMode );
			
			if ( mSettings->stringValue( Settings::VideoMode ) == "soft" )
			{
				args << "-scalemode" << mSettings->stringValue( Settings::ScaleMode );
			}
			
			if ( !mSettings->boolValue( Settings::FullScreen ) )
			{
				args << "-window";
			}
			
			if ( mSettings->boolValue( Settings::Maximize ) )
			{
				args << "-maximize";
			}
			
			if ( mSettings->boolValue( Settings::KeepAspectRatio ) )
			{
				args << "-keepaspect";
			}
			
			if ( mSettings->boolValue( Settings::AllowDoubleStretchFactors ) )
			{
				args << "-unevenstretch";
			}
			
			if ( mSettings->boolValue( Settings::WaitVBLANK ) )
			{
				args << "-waitvsync";
			}
			
			// others
			args << "-rompath" << mSettings->stringValue( Settings::Bios ) << "-cart" << mMachineRomPair.second;
			
			break;
		case ProcessQuery::ListXml:
			args << "-listxml";
			break;
		case ProcessQuery::IDLE:
			return false;
			break;
	}
	
	for ( int i = 0; i < args.count(); i++ )
	{
		QString arg = args.at( i );
		
		if ( arg.contains( " " ) )
		{
			arg.prepend( "\"" ).append( "\"" );
			args[ i ] = arg;
		}
	}
	
	emit log( tr( "Running command: %1 %2" ).arg( mSettings->stringValue( Settings::Binary ) ).arg( args.join( " " ) ) );
	start( mSettings->stringValue( Settings::Binary ), args );
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
