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
	leBinaryFile->setText( mSettings->binary() );
	leBiosPath->setText( mSettings->biosPath() );
	
	// roms
	mRomsPaths = mSettings->romsPaths();
	const int index = cbRomsPath->currentIndex();
	const QString name = cbRomsPath->itemData( index ).toString();
	leRomsPath->setText( mRomsPaths.value( name ) );
}

void UISettings::restoreDefaults()
{
	// general
	leBinaryFile->setText( "sdlmess" );
	leBiosPath->setText( QString( "%1/.mess/bios" ).arg( QDir::homePath() ) );
	
	// roms
	mRomsPaths.clear();
	leRomsPath->clear();
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

void UISettings::on_dbbButtons_clicked( QAbstractButton* button )
{
	if ( dbbButtons->standardButton( button ) == QDialogButtonBox::RestoreDefaults )
	{
		restoreDefaults();
	}
}

void UISettings::accept()
{
	mSettings->setBinary( leBinaryFile->text() );
	mSettings->setBiosPath( leBiosPath->text() );
	mSettings->setRomsPaths( mRomsPaths );
	mSettings->save();
	
	QDialog::accept();
}
