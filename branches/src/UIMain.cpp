#include "UIMain.h"
#include "UISettings.h"
#include "Settings.h"
#include "MachineModel.h"
#include "MachineItem.h"
#include "MachineFilterModel.h"
#include "RomModel.h"
#include "RomFilterModel.h"

#include <QFileDialog>

#include <QDebug>

UIMain::UIMain( QWidget* parent )
	: QMainWindow( parent )
{
	mSettings = new Settings;
	
	mProcessQuery = new ProcessQuery( mSettings, this );
	
	mMachineModel = new MachineModel( this );
	mMachineFilterModel = new MachineFilterModel( mMachineModel );
	mRomsModel = new RomModel( this );
	mRomFilterModel = new RomFilterModel( mRomsModel );
	
	mMachineModel->setIconsPath( qApp->applicationDirPath().append( "/src/resources/machines" ) );
	
	setupUi( this );
	
	seMachinesFilter->setPromptText( tr( "Machines filter..." ) );
	seRomsFilter->setPromptText( tr( "Roms filter..." ) );
	tvMachines->setModel( mMachineFilterModel );
	tvRoms->setModel( mRomFilterModel );
	tvRoms->header()->QHeaderView::setResizeMode( 0, QHeaderView::ResizeToContents );
	tvRoms->header()->QHeaderView::setResizeMode( 1, QHeaderView::Stretch );
	tvRoms->header()->QHeaderView::setResizeMode( 2, QHeaderView::ResizeToContents );
	tvRoms->header()->QHeaderView::setResizeMode( 3, QHeaderView::ResizeToContents );
	
	connect( mProcessQuery, SIGNAL( log( const QString& ) ), this, SLOT( appendLog( const QString& ) ) );
	connect( mMachineModel, SIGNAL( ready() ), this, SLOT( machineModel_ready() ) );
	connect( seMachinesFilter, SIGNAL( searchChanged( const QString& ) ), mMachineFilterModel, SLOT( setFilterWildcard( const QString& ) ) );
	connect( mRomsModel, SIGNAL( ready() ), this, SLOT( romsModel_ready() ) );
	
	reloadSettings();
}

UIMain::~UIMain()
{
	const QModelIndex machineIndex = mMachineFilterModel->mapToSource( tvMachines->currentIndex() );
	const MachineItem* machineItem = mMachineModel->itemFromIndex( machineIndex );
	
	if ( machineItem )
	{
		mSettings->setStringValue( Settings::CurrentMachine, machineItem->infos().data( MachineInfos::Name ) );
	}
	
	mSettings->setStringValue( Settings::MachineFilter, seMachinesFilter->text() );
	mSettings->setStringValue( Settings::RomsFilter, seRomsFilter->text() );
	
	delete mSettings;
}

void UIMain::appendLog( const QString& message )
{
	pteLog->appendPlainText( message );
}

void UIMain::reloadSettings()
{
	seMachinesFilter->setText( mSettings->stringValue( Settings::MachineFilter ) );
	seRomsFilter->setText( mSettings->stringValue( Settings::RomsFilter) );
	
	mProcessQuery->listXml();
}

void UIMain::machineModel_ready()
{
	const QString name = mSettings->stringValue( Settings::CurrentMachine );
	const QModelIndex machineIndex = mMachineModel->machineIndex( name );
	const QModelIndex proxyIndex = mMachineFilterModel->mapFromSource( machineIndex );
	
	mMachineFilterModel->setFilterWildcard( seMachinesFilter->text() );
	tvMachines->setCurrentIndex( proxyIndex );
	tvMachines->scrollTo( proxyIndex, QAbstractItemView::PositionAtTop );
	
	if ( proxyIndex.isValid() )
	{
		on_tvMachines_activated( proxyIndex );
	}
}

void UIMain::romsModel_ready()
{
	const int count = mRomsModel->rowCount();
	
	lTotalRoms->setText( tr( "%1 roms found." ).arg( count ) );
}

void UIMain::on_aSettings_triggered()
{
	UISettings* dlg = new UISettings( mSettings, mMachineModel->rootItems(), this );
	connect( dlg, SIGNAL( accepted() ), this, SLOT( reloadSettings() ) );
	dlg->open();
}

void UIMain::on_aQuit_triggered()
{
	qApp->quit();
}

void UIMain::on_tvMachines_activated( const QModelIndex& proxyIndex )
{
	const QModelIndex machineIndex = mMachineFilterModel->mapToSource( proxyIndex );
	const MachineItem* root = mMachineModel->rootItem();
	const MachineItem* machine = mMachineModel->itemFromIndex( machineIndex );
	const MachineItem* parentMachine = machine->parent();
	QString path = mSettings->romsPath( machine->infos().data( MachineInfos::Name ) );
	
	if ( path.isEmpty() )
	{
		if ( parentMachine != root )
		{
			path = mSettings->romsPath( parentMachine->infos().data( MachineInfos::Name ) );
		}
		
		if ( path.isNull() )
		{
			path = QFileDialog::getExistingDirectory( this );
			
			if ( !path.isNull() )
			{
				const MachineItem* item = parentMachine == root ? machine : parentMachine;
				
				mSettings->setRomsPath( item->infos().data( MachineInfos::Name ), path );
			}
		}
	}
	
	lMachineIcon->setPixmap( machine->icon() );
	lMachineIcon->setVisible( !lMachineIcon->pixmap()->isNull() );
	teMachineInfos->setHtml( machine->infos().toHtml() );
	mRomsModel->refresh( machine, mSettings, seRomsFilter->text() );
	lTotalRoms->setText( tr( "Listing roms..." ) );
}

void UIMain::on_seRomsFilter_searchChanged( const QString& text )
{
	const QModelIndex proxyIndex = tvMachines->currentIndex();
	const QModelIndex machineIndex = mMachineFilterModel->mapToSource( proxyIndex );
	const MachineItem* machine = mMachineModel->itemFromIndex( machineIndex );
	
	mRomsModel->refresh( machine, mSettings, text );
	lTotalRoms->setText( tr( "Searching roms..." ) );
}

void UIMain::on_tvRoms_activated( const QModelIndex& proxyIndex )
{
	const QModelIndex index = mRomFilterModel->mapToSource( proxyIndex );
	const QModelIndex machineIndex = mMachineFilterModel->mapToSource( tvMachines->currentIndex() );
	MachineItem* machineItem = mMachineModel->itemFromIndex( machineIndex );
	
	if ( machineItem )
	{
		if ( isVisible() )
		{
			setVisible( false );
		}
		
		mProcessQuery->startRom( machineItem, mRomsModel->filePath( index ) );
	}
}

void UIMain::on_processQuery_error( ProcessQuery::Task task, QProcess::ProcessError error )
{
	const QString message = tr( "*** Error %1 on task %2" ).arg( error ).arg( task );
	appendLog( message );
}

void UIMain::on_processQuery_finished( int exitCode, QProcess::ExitStatus exitStatus )
{
	const QString message = tr( "*** Finished with exitCode %1 and exitStatus %2" ).arg( exitCode ).arg( exitStatus );
	appendLog( message );
	
	if ( !isVisible() )
	{
		setVisible( true );
	}
}

void UIMain::on_processQuery_listXmlFinished( const QDomDocument& document, bool error, const QString& errorMsg, const QPoint& errorPosition )
{
	if ( error )
	{
		const QString message = tr( "'%1' at line %2, column %3" ).arg( errorMsg ).arg( errorPosition.y() ).arg( errorPosition.x() );
		appendLog( message );
	}
	else
	{
		mMachineModel->setDocument( document );
		//appendLog( document.toString() );
	}
	
	const MachinesCount count = mMachineModel->count();
	const QString text = tr( "<b>Total: </b>%1 | <b>Unique: </b>%2 | <b>Clones: </b>%3" )
		.arg( count.total )
		.arg( count.unique )
		.arg( count.clones );
	
	lTotalMachines->setText( text );
}
