#include "UISettings.h"
#include "Settings.h"
#include "MachineItem.h"

#include <QFileDialog>

UISettings::UISettings( Settings* settings, const MachineItemList& machines, QWidget* parent )
	: QDialog( parent )
{
	Q_ASSERT( settings );
	mSettings = settings;
	mMachines = machines;
	
	setupUi( this );
	setAttribute( Qt::WA_DeleteOnClose );
	
	foreach ( MachineItem* item, mMachines )
	{
		cbRomsPath->addItem( item->text(), item->infos().data( MachineInfos::Name ) );
	}
	
	if ( mSettings->isInitialized() )
	{
		initSettings();
	}
	else
	{
		restoreDefaults();
	}
}

UISettings::~UISettings()
{
}

void UISettings::initSettings()
{
	// general
	leBinaryFile->setText( mSettings->stringValue( Settings::Binary ) );
	leBiosPath->setText( mSettings->stringValue( Settings::Bios ) );
	
	// roms
	mRomsPaths = mSettings->romsPaths();
	const int index = cbRomsPath->currentIndex();
	const QString name = cbRomsPath->itemData( index ).toString();
	leRomsPath->setText( mRomsPaths.value( name ) );
	
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

void UISettings::on_cbRomsPath_currentIndexChanged( int index )
{
	const QString name = cbRomsPath->itemData( index ).toString();
	leRomsPath->setText( mRomsPaths.value( name ) );
}

void UISettings::on_tbRomsPathSet_clicked()
{
	const int index = cbRomsPath->currentIndex();
	const QString name = cbRomsPath->itemData( index ).toString();
	mRomsPaths[ name ] = leRomsPath->text();
}

void UISettings::on_tbRomsPath_clicked()
{
	const int index = cbRomsPath->currentIndex();
	const QString name = cbRomsPath->itemData( index ).toString();
	const QString path = getExistingDirectory( tr( "Select a roms path for '%1'" ).arg( name ), leRomsPath->text() );
	
	if ( !path.isEmpty() )
	{
		leRomsPath->setText( path );
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
