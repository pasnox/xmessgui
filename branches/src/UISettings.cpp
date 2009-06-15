#include "UISettings.h"
#include "Settings.h"
#include "MachineItem.h"
#include "MachineFilterModel.h"

#include <QFileDialog>

UISettings::UISettings( Settings* settings, MachineModel* machineModel, QWidget* parent )
	: QDialog( parent )
{
	Q_ASSERT( settings );
	Q_ASSERT( machineModel );
	mSettings = settings;
	mMachineModel = machineModel;
	mMachineFilterModel = new MachineFilterModel( mMachineModel );
	
	setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose );
	tvRomsPath->setModel( mMachineFilterModel );
	
	if ( mSettings->isInitialized() )
	{
		initSettings();
	}
	else
	{
		restoreDefaults();
	}
	
	seMachineFilter->setPromptText( tr( "Machines filter..." ) );
	
	connect( seMachineFilter, SIGNAL( searchChanged( const QString& ) ), mMachineFilterModel, SLOT( setFilterWildcard( const QString& ) ) );
}

UISettings::~UISettings()
{
}

void UISettings::initSettings()
{
	// general
	leBinaryFile->setText( mSettings->stringValue( Settings::Binary ) );
	leBiosPath->setText( mSettings->stringValue( Settings::Bios ) );
	leResourcesPath->setText( mSettings->stringValue( Settings::Resources ) );
	
	// roms
	mRomsPaths = mSettings->romsPaths();
	const QModelIndex proxyIndex = tvRomsPath->currentIndex();
	const QModelIndex index = mMachineFilterModel->mapToSource( proxyIndex );
	MachineItem* machine = mMachineModel->itemFromIndex( index );
	
	if ( index.isValid() )
	{
		const QString name = machine->infos().data( MachineInfos::Name );
		
		leRomsPath->setText( mRomsPaths.value( name ) );
	}
	
	// performance
	cbMultithreading->setChecked( mSettings->boolValue( Settings::Multithreading ) );
	cbSDLFPS->setChecked( mSettings->boolValue( Settings::SDLFPS ) );
	
	// video
	cbVideoMode->setCurrentIndex( cbVideoMode->findText( mSettings->stringValue( Settings::VideoMode ) ) );
	cbScaleMode->setCurrentIndex( cbScaleMode->findText( mSettings->stringValue( Settings::ScaleMode ) ) );
	cbFullScreen->setChecked( mSettings->boolValue( Settings::FullScreen ) );
	cbMaximize->setChecked( mSettings->boolValue( Settings::Maximize ) );
	cbKeepAspectRatio->setChecked( mSettings->boolValue( Settings::KeepAspectRatio ) );
	cbAllowDoubleStretchFactors->setChecked( mSettings->boolValue( Settings::AllowDoubleStretchFactors ) );
	cbWaitVBLANK->setChecked( mSettings->boolValue( Settings::WaitVBLANK ) );
	
	// misc
	cbSkipGameInformations->setChecked( mSettings->boolValue( Settings::SkipGameInformations ) );
	cbSkipWarnings->setChecked( mSettings->boolValue( Settings::SkipWarnings ) );
	cbCheat->setChecked( mSettings->boolValue( Settings::Cheat ) );
	
	// states
	cbAutoSave->setChecked( mSettings->boolValue( Settings::AutoSave ) );
}

void UISettings::restoreDefaults()
{
	// general
	leBinaryFile->setText( "sdlmess" );
	leBiosPath->setText( QString( "%1/.mess/bios" ).arg( QDir::homePath() ) );
	leResourcesPath->setText( QString( "%1/.mess/resources" ).arg( QDir::homePath() ) );
	
	// roms
	mRomsPaths.clear();
	leRomsPath->clear();
	
	// performance
	cbMultithreading->setChecked( false );
	cbSDLFPS->setChecked( false );
	
	// video
	cbVideoMode->setCurrentIndex( cbVideoMode->findText( "opengl" ) );
	cbScaleMode->setCurrentIndex( cbScaleMode->findText( "none" ) );
	cbFullScreen->setChecked( false );
	cbMaximize->setChecked( false );
	cbKeepAspectRatio->setChecked( false );
	cbAllowDoubleStretchFactors->setChecked( false );
	cbWaitVBLANK->setChecked( false );
	
	// misc
	cbSkipGameInformations->setChecked( false );
	cbSkipWarnings->setChecked( false );
	cbCheat->setChecked( false );
	
	// states
	cbAutoSave->setChecked( false );
}

QString UISettings::getOpenFileName( const QString& text, const QString& fileName, const QString& filter )
{
	return QFileDialog::getOpenFileName( this, text, fileName, filter );
}

QString UISettings::getExistingDirectory( const QString& text, const QString& path )
{
	return QFileDialog::getExistingDirectory( this, text, path );
}

void UISettings::on_tbBinaryFile_clicked()
{
	const QString fn = getOpenFileName( tr( "Select your sdlmess binary file" ), leBinaryFile->text() );
	
	if ( !fn.isEmpty() )
	{
		leBinaryFile->setText( fn );
	}
}

void UISettings::on_tbBiosPath_clicked()
{
	const QString path = getExistingDirectory( tr( "Select your sdlmess bios path" ), leBiosPath->text() );
	
	if ( !path.isEmpty() )
	{
		leBiosPath->setText( path );
	}
}

void UISettings::on_tbResourcesPath_clicked()
{
	const QString path = getExistingDirectory( tr( "Select your resources path" ), leResourcesPath->text() );
	
	if ( !path.isEmpty() )
	{
		leResourcesPath->setText( path );
	}
}

void UISettings::on_tvRomsPath_activated( const QModelIndex &proxyIndex )
{
	const QModelIndex index = mMachineFilterModel->mapToSource( proxyIndex );
	MachineItem* machine = mMachineModel->itemFromIndex( index );
	
	if ( machine )
	{
		const QString name = machine->infos().data( MachineInfos::Name );
		
		leRomsPath->setText( mRomsPaths.value( name ) );
	}
}

void UISettings::on_tbRomsPathSet_clicked()
{
	const QModelIndex proxyIndex = tvRomsPath->currentIndex();
	const QModelIndex index = mMachineFilterModel->mapToSource( proxyIndex );
	MachineItem* machine = mMachineModel->itemFromIndex( index );
	
	if ( machine )
	{
		const QString name = machine->infos().data( MachineInfos::Name );
		mRomsPaths[ name ] = leRomsPath->text();
	}
}

void UISettings::on_tbRomsPath_clicked()
{
	const QModelIndex proxyIndex = tvRomsPath->currentIndex();
	const QModelIndex index = mMachineFilterModel->mapToSource( proxyIndex );
	MachineItem* machine = mMachineModel->itemFromIndex( index );
	
	if ( machine )
	{
		const QString name = machine->infos().data( MachineInfos::Name );
		const QString path = getExistingDirectory( tr( "Select a roms path for '%1'" ).arg( name ), leRomsPath->text() );
		
		if ( !path.isEmpty() )
		{
			leRomsPath->setText( path );
		}
	}
}

void UISettings::on_cbVideoMode_currentIndexChanged( const QString& text )
{
	cbScaleMode->setEnabled( text == "soft" );
}

void UISettings::on_dbbButtons_clicked( QAbstractButton* button )
{
	if ( dbbButtons->standardButton( button ) == QDialogButtonBox::RestoreDefaults )
	{
		restoreDefaults();
	}
}

void UISettings::accept()
{
	// general
	mSettings->setStringValue( Settings::Binary, leBinaryFile->text() );
	mSettings->setStringValue( Settings::Bios, leBiosPath->text() );
	mSettings->setStringValue( Settings::Resources, leResourcesPath->text() );
	
	// roms
	mSettings->setRomsPaths( mRomsPaths );
	
	// performance
	mSettings->setBoolValue( Settings::Multithreading, cbMultithreading->isChecked() );
	mSettings->setBoolValue( Settings::SDLFPS, cbSDLFPS->isChecked() );
	
	// video
	mSettings->setStringValue( Settings::VideoMode, cbVideoMode->currentText() );
	mSettings->setStringValue( Settings::ScaleMode, cbScaleMode->currentText() );
	mSettings->setBoolValue( Settings::FullScreen, cbFullScreen->isChecked() );
	mSettings->setBoolValue( Settings::Maximize, cbMaximize->isChecked() );
	mSettings->setBoolValue( Settings::KeepAspectRatio, cbKeepAspectRatio->isChecked() );
	mSettings->setBoolValue( Settings::AllowDoubleStretchFactors, cbAllowDoubleStretchFactors->isChecked() );
	mSettings->setBoolValue( Settings::WaitVBLANK, cbWaitVBLANK->isChecked() );
	
	// misc
	mSettings->setBoolValue( Settings::SkipGameInformations, cbSkipGameInformations->isChecked() );
	mSettings->setBoolValue( Settings::SkipWarnings, cbSkipWarnings->isChecked() );
	mSettings->setBoolValue( Settings::Cheat, cbCheat->isChecked() );
	
	// states
	mSettings->setBoolValue( Settings::AutoSave, cbAutoSave->isChecked() );
	
	mSettings->save();
	
	QDialog::accept();
}
