#include "MachineInfos.h"

// iGenericDatas

iGenericDatas::iGenericDatas( const QDomElement& element )
{
	QDomNamedNodeMap attributes = element.attributes();
	
	for ( int i = 0; i < attributes.count(); i++ )
	{
		QDomNode node = attributes.item( i );
		const QString name = node.nodeName();
		const QString value = node.nodeValue();
		
		mDatas[ name ] = value;
	}
}

QString iGenericDatas::toHtml( int nbspace ) const
{
	const QString spaces = QString().fill( ' ', nbspace ).replace( " ", "&nbsp;" );
	QString html;
	
	foreach ( const QString& key, mDatas.keys() )
	{
		html += QString( "%1%2: %3<br />" ).arg( spaces ).arg( key ).arg( mDatas[ key ] );
	}
	
	return html;
}

QMap<QString, QString> iGenericDatas::datas() const
{
	return mDatas;
}

QString iGenericDatas::data( const QString& key ) const
{
	return mDatas.value( key );
}

// iBios

iBios::iBios( const QDomElement& element )
	: iGenericDatas( element )
{
}

QString iBios::data( iBios::Type type ) const
{
	switch ( type )
	{
		case iBios::Default:
			return iGenericDatas::data( "default" );
			break;
		case iBios::Description:
			return iGenericDatas::data( "description" );
			break;
		case iBios::Name:
			return iGenericDatas::data( "name" );
			break;
	}
	
	return QString::null;
}

// iRom

iRom::iRom( const QDomElement& element )
	: iGenericDatas( element )
{
}

QString iRom::data( iRom::Type type ) const
{
	switch ( type )
	{
		case iRom::Status:
			return iGenericDatas::data( "status" );
			break;
		case iRom::Offset:
			return iGenericDatas::data( "offset" );
			break;
		case iRom::Size:
			return iGenericDatas::data( "size" );
			break;
		case iRom::Region:
			return iGenericDatas::data( "region" );
			break;
		case iRom::Sha1:
			return iGenericDatas::data( "sha1" );
			break;
		case iRom::Bios:
			return iGenericDatas::data( "bios" );
			break;
		case iRom::Name:
			return iGenericDatas::data( "name" );
			break;
		case iRom::Crc:
			return iGenericDatas::data( "crc" );
			break;
	}
	
	return QString::null;
}

// iChip

iChip::iChip( const QDomElement& element )
	: iGenericDatas( element )
{
}

QString iChip::data( iChip::Type type ) const
{
	switch ( type )
	{
		case iChip::Tag:
			return iGenericDatas::data( "tag" );
			break;
		case iChip::Clock:
			return iGenericDatas::data( "clock" );
			break;
		case iChip::Cpu:
			return iGenericDatas::data( "cpu" );
			break;
		case iChip::Name:
			return iGenericDatas::data( "name" );
			break;
	}
	
	return QString::null;
}

// iDisplay

iDisplay::iDisplay( const QDomElement& element )
	: iGenericDatas( element )
{
}

QString iDisplay::data( iDisplay::Type type ) const
{
	switch ( type )
	{
		case iDisplay::Width:
			return iGenericDatas::data( "width" );
			break;
		case iDisplay::Height:
			return iGenericDatas::data( "height" );
			break;
		case iDisplay::PixClock:
			return iGenericDatas::data( "pixclock" );
			break;
		case iDisplay::VBStart:
			return iGenericDatas::data( "vbstart" );
			break;
		case iDisplay::VBEnd:
			return iGenericDatas::data( "vbend" );
			break;
		case iDisplay::_Type:
			return iGenericDatas::data( "type" );
			break;
		case iDisplay::HTotal:
			return iGenericDatas::data( "htotal" );
			break;
		case iDisplay::VTotal:
			return iGenericDatas::data( "vtotal" );
			break;
		case iDisplay::HBStart:
			return iGenericDatas::data( "hbstart" );
			break;
		case iDisplay::HBEnd:
			return iGenericDatas::data( "hbend" );
			break;
		case iDisplay::Rotate:
			return iGenericDatas::data( "rotate" );
			break;
		case iDisplay::Refresh:
			return iGenericDatas::data( "refresh" );
			break;
	}
	
	return QString::null;
}

// iSound

iSound::iSound( const QDomElement& element )
	: iGenericDatas( element )
{
}

QString iSound::data( iSound::Type type ) const
{
	switch ( type )
	{
		case iSound::Channels:
			return iGenericDatas::data( "channels" );
			break;
	}
	
	return QString::null;
}

// iDriver

iDriver::iDriver( const QDomElement& element )
	: iGenericDatas( element )
{
}

QString iDriver::data( iDriver::Type type ) const
{
	switch ( type )
	{
		case iDriver::Status:
			return iGenericDatas::data( "status" );
			break;
		case iDriver::Emulation:
			return iGenericDatas::data( "emulation" );
			break;
		case iDriver::Graphic:
			return iGenericDatas::data( "graphic" );
			break;
		case iDriver::Sound:
			return iGenericDatas::data( "sound" );
			break;
		case iDriver::SaveState:
			return iGenericDatas::data( "savestate" );
			break;
		case iDriver::Color:
			return iGenericDatas::data( "color" );
			break;
		case iDriver::PaletteSize:
			return iGenericDatas::data( "palettesize" );
			break;
	}
	
	return QString::null;
}

// iControl

iControl::iControl( const QDomElement& element )
	: iGenericDatas( element )
{
}

QString iControl::data( iControl::Type type ) const
{
	switch ( type )
	{
		case iControl::KeyDelta:
			return iGenericDatas::data( "keydelta" );
			break;
		case iControl::Reverse:
			return iGenericDatas::data( "reverse" );
			break;
		case iControl::Minimum:
			return iGenericDatas::data( "minimum" );
			break;
		case iControl::Maximum:
			return iGenericDatas::data( "maximum" );
			break;
		case iControl::_Type:
			return iGenericDatas::data( "type" );
			break;
		case iControl::Sensitivity:
			return iGenericDatas::data( "sensitivity" );
			break;
	}
	
	return QString::null;
}

// iInput

iInput::iInput( const QDomElement& element )
	: iGenericDatas( element )
{
	const QDomNodeList nodes = element.childNodes();
	
	for ( int i = 0; i < nodes.count(); i++ )
	{
		const QDomElement element = nodes.at( i ).toElement();
		
		mControls << iControl( element );
	}
}

QString iInput::toHtml( int nbspace ) const
{
	const QString spaces = QString().fill( ' ', nbspace ).replace( " ", "&nbsp;" );
	QString html = iGenericDatas::toHtml( nbspace );
	
	if ( !mControls.isEmpty() )
	{
		html += QString( "%1<b>Controls</b>:<br />%2" ).arg( spaces ).arg( iGenericDatas::toHtml( mControls, nbspace ) );
	}
	
	return html;
}

iControlList iInput::controls() const
{
	return mControls;
}

// iDevice

iDevice::iDevice( const QDomElement& element )
	: iGenericDatas( element )
{
	const QDomNodeList nodes = element.childNodes();
	
	for ( int i = 0; i < nodes.count(); i++ )
	{
		const QDomNode node = nodes.at( i );
		const QString nodeName = node.nodeName();
		
		if ( nodeName == "instance" )
		{
			const QDomNamedNodeMap attributes = node.attributes();
			
			for ( int j = 0; j < attributes.count(); j++ )
			{
				const QDomNode attribute = attributes.item( j );
				
				mDatas[ attribute.nodeName() ] = attribute.nodeValue();
			}
		}
		else if ( nodeName == "extension" )
		{
			mExtensions << node.attributes().namedItem( "name" ).nodeValue();
		}
	}
}

QString iDevice::toHtml( int nbspace ) const
{
	const QString spaces = QString().fill( ' ', nbspace ).replace( " ", "&nbsp;" );
	QString html = iGenericDatas::toHtml( nbspace );
	
	if ( !mExtensions.isEmpty() )
	{
		html += QString( "%1extension: %2<br />" ).arg( spaces ).arg( mExtensions.join( ";" ) );
	}
	
	return html;
}

QString iDevice::data( iDevice::Type type ) const
{
	switch ( type )
	{
		case iDevice::Tag:
			return iGenericDatas::data( "tag" );
			break;
		case iDevice::_Type:
			return iGenericDatas::data( "type" );
			break;
		case iDevice::Mandatory:
			return iGenericDatas::data( "mandatory" );
			break;
		case iDevice::BriefName:
			return iGenericDatas::data( "briefname" );
			break;
		case iDevice::Name:
			return iGenericDatas::data( "name" );
			break;
	}
	
	return QString::null;
}

QStringList iDevice::extensions() const
{
	return mExtensions;
}

// iDipValue

iDipValue::iDipValue( const QDomElement& element )
	: iGenericDatas( element )
{
}

QString iDipValue::data( iDipValue::Type type ) const
{
	switch ( type )
	{
		case iDipValue::Default:
			return iGenericDatas::data( "default" );
			break;
		case iDipValue::Name:
			return iGenericDatas::data( "name" );
			break;
	}
	
	return QString::null;
}

// iDipSwitch

iDipSwitch::iDipSwitch( const QDomElement& element )
	: iGenericDatas( element )
{
	const QDomNodeList nodes = element.childNodes();
	
	for ( int i = 0; i < nodes.count(); i++ )
	{
		const QDomElement element = nodes.at( i ).toElement();
		
		mDipValues << iDipValue( element );
	}
}

QString iDipSwitch::toHtml( int nbspace ) const
{
	const QString spaces = QString().fill( ' ', nbspace ).replace( " ", "&nbsp;" );
	QString html = iGenericDatas::toHtml( nbspace );
	
	if ( !mDipValues.isEmpty() )
	{
		html += QString( "%1<b>DipSwitch</b>:<br />%2" ).arg( spaces ).arg( iGenericDatas::toHtml( mDipValues, nbspace ) );
	}
	
	return html;
}

QString iDipSwitch::data( iDipSwitch::Type type ) const
{
	switch ( type )
	{
		case iDipSwitch::Name:
			return iGenericDatas::data( "name" );
			break;
	}
	
	return QString::null;
}

iDipValueList iDipSwitch::dipValues() const
{
	return mDipValues;
}

// MachineInfos

MachineInfos::MachineInfos( const QDomElement& element )
	: iGenericDatas( element )
{
	const QDomNodeList nodes = element.childNodes();
	
	for ( int i = 0; i < nodes.count(); i++ )
	{
		const QDomNode node = nodes.at( i );
		
		if ( node.attributes().isEmpty() )
		{
			mDatas[ node.nodeName() ] = node.firstChild().toText().data();
		}
		else
		{
			const QString name = node.nodeName();
			
			if ( name == "bios" )
			{
				mBios << iBios( node.toElement() );
			}
			else if ( name == "rom" )
			{
				mRoms << iRom( node.toElement() );
			}
			else if ( name == "display" )
			{
				mDisplay = iDisplay( node.toElement() );
			}
			else if ( name == "sound" )
			{
				mSound = iSound( node.toElement() );
			}
			else if ( name == "driver" )
			{
				mDriver = iDriver( node.toElement() );
			}
			else if ( name == "input" )
			{
				mInputs = iInput( node.toElement() );
			}
			else if ( name == "device" )
			{
				mDevices << iDevice( node.toElement() );
			}
			else if ( name == "dipswitch" )
			{
				mDipSwitchs << iDipSwitch( node.toElement() );
			}
		}
	}
}

QString MachineInfos::toHtml( int nbspace ) const
{
	const int tabSize = 2;
	QString html = QString( "<b>Machine</b>:<br />%1" ).arg( iGenericDatas::toHtml( nbspace +tabSize ) );
	
	if ( !mBios.isEmpty() )
	{
		html += QString( "<b>Bios</b>:<br />%1" ).arg( iGenericDatas::toHtml( mBios, nbspace +tabSize ) );
	}
	if ( !mRoms.isEmpty() )
	{
		html += QString( "<b>Roms</b>:<br />%1" ).arg( iGenericDatas::toHtml( mRoms, nbspace +tabSize ) );
	}
	html += QString( "<b>Display</b>:<br />%1" ).arg( mDisplay.toHtml( nbspace +tabSize ) );
	html += QString( "<b>Sound</b>:<br />%1" ).arg( mSound.toHtml( nbspace +tabSize ) );
	html += QString( "<b>Driver</b>:<br />%1" ).arg( mDriver.toHtml( nbspace +tabSize ) );
	html += QString( "<b>Inputs</b>:<br />%1" ).arg( mInputs.toHtml( nbspace +tabSize ) );
	if ( !mDevices.isEmpty() )
	{
		html += QString( "<b>Devices</b>:<br />%1" ).arg( iGenericDatas::toHtml( mDevices, nbspace +tabSize ) );
	}
	if ( !mDipSwitchs.isEmpty() )
	{
		html += QString( "<b>DipSwitchs</b>:<br />%1" ).arg( iGenericDatas::toHtml( mDipSwitchs, nbspace +tabSize ) );
	}
	
	return html;
}

QString MachineInfos::data( MachineInfos::Type type ) const
{
	switch ( type )
	{
		case MachineInfos::Name:
			return iGenericDatas::data( "name" );
			break;
		case MachineInfos::CloneOf:
			return iGenericDatas::data( "cloneof" );
			break;
		case MachineInfos::SourceFile:
			return iGenericDatas::data( "sourcefile" );
			break;
		case MachineInfos::Description:
			return iGenericDatas::data( "description" );
			break;
		case MachineInfos::Year:
			return iGenericDatas::data( "Year" );
			break;
		case MachineInfos::Manufacturer:
			return iGenericDatas::data( "manufacturer" );
			break;
	}
	
	return QString::null;
}
