#ifndef MACHINEITEM_H
#define MACHINEITEM_H

#include <QList>
#include <QDomNode>
#include <QPixmap>
#include <QMap>
#include <QBrush>

#include <QDebug>

class iGenericDatas
{
public:
	iGenericDatas( const QDomElement& element = QDomElement() )
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
	
	virtual QString toHtml( int nbspace = 0 ) const
	{
		const QString space = QString().fill( ' ', nbspace ).replace( " ", "&nbsp;" );
		QString html;
		
		foreach ( const QString& key, mDatas.keys() )
		{
			html += QString( "%1%2: %3<br />" ).arg( space ).arg( key ).arg( mDatas[ key ] );
		}
		
		return html;
	}
	
	template <class T>
	static QString toHtml( const QList<T>& datas, int nbspace = 0 )
	{
		QString html;
		
		foreach ( const T& data, datas )
		{
			html += data.toHtml( nbspace );
		}
		
		return html;
	}
	
	QMap<QString, QString> datas() const
	{ return mDatas; }

protected:
	QMap<QString, QString> mDatas;
};

/*
<biosset default="yes" description="Panasonic FZ-10 R.E.A.L. 3DO Interactive Multiplayer" name="panafz10" />
*/
class iBios : public iGenericDatas
{
public:
	iBios( const QDomElement& element = QDomElement() )
		: iGenericDatas( element ) {}
	
	QString _default() const
	{ return mDatas.value( "default" ); }
	
	QString description() const
	{ return mDatas.value( "description" ); }
	
	QString name() const
	{ return mDatas.value( "name" ); }
};

typedef QList<iBios> iBiosList;

/*
<rom offset="0" size="1048576" region="user1" sha1="3c912300775d1ad730dc35757e279c274c0acaad" bios="panafz10" name="panafz10.bin" crc="58242cee" />
<rom status="nodump" offset="0" size="1048576" region="user1" bios="gsalive2" name="gsalive2.bin" />
*/
class iRom : public iGenericDatas
{
public:
	iRom( const QDomElement& element = QDomElement() )
		: iGenericDatas( element ) {}
	
	QString status() const
	{ return mDatas.value( "status" ); }
	
	QString offset() const
	{ return mDatas.value( "offset" ); }
	
	QString size() const
	{ return mDatas.value( "size" ); }
	
	QString region() const
	{ return mDatas.value( "region" ); }
	
	QString sha1() const
	{ return mDatas.value( "sha1" ); }
	
	QString bios() const
	{ return mDatas.value( "bios" ); }
	
	QString name() const
	{ return mDatas.value( "name" ); }
	
	QString crc() const
	{ return mDatas.value( "crc" ); }
};

typedef QList<iRom> iRomList;

/*
<chip tag="maincpu" clock="12500000" type="cpu" name="ARM7" />
*/
class iChip : public iGenericDatas
{
public:
	iChip( const QDomElement& element = QDomElement() )
		: iGenericDatas( element ) {}
	
	QString tag() const
	{ return mDatas.value( "tag" ); }
	
	QString clock() const
	{ return mDatas.value( "clock" ); }
	
	QString type() const
	{ return mDatas.value( "cpu" ); }
	
	QString name() const
	{ return mDatas.value( "name" ); }
};

typedef QList<iChip> iChipList;

/*
<display width="640" height="480" pixclock="20160000" vbstart="480" vbend="0" type="raster" htotal="640" hbend="0" hbstart="640" rotate="0" vtotal="525" refresh="60.000000" />
*/
class iDisplay : public iGenericDatas
{
public:
	iDisplay( const QDomElement& element = QDomElement() )
		: iGenericDatas( element ) {}
	
	QString width() const
	{ return mDatas.value( "width" ); }
	
	QString height() const
	{ return mDatas.value( "height" ); }
	
	QString pixclock() const
	{ return mDatas.value( "pixclock" ); }
	
	QString vbstart() const
	{ return mDatas.value( "vbstart" ); }
	
	QString vbend() const
	{ return mDatas.value( "vbend" ); }
	
	QString type() const
	{ return mDatas.value( "type" ); }
	
	QString htotal() const
	{ return mDatas.value( "htotal" ); }
	
	QString vtotal() const
	{ return mDatas.value( "vtotal" ); }
	
	QString hbstart() const
	{ return mDatas.value( "hbstart" ); }
	
	QString hbend() const
	{ return mDatas.value( "hbend" ); }
	
	QString rotate() const
	{ return mDatas.value( "rotate" ); }
	
	QString refresh() const
	{ return mDatas.value( "refresh" ); }
};

/*
<sound channels="0" />
*/
class iSound : public iGenericDatas
{
public:
	iSound( const QDomElement& element = QDomElement() )
		: iGenericDatas( element ) {}
	
	QString channels() const
	{ return mDatas.value( "channels" ); }
};

/*
<driver status="preliminary" emulation="preliminary" graphic="good" sound="good" savestate="unsupported" color="good" palettesize="0" />
*/
class iDriver : public iGenericDatas
{
public:
	iDriver( const QDomElement& element = QDomElement() )
		: iGenericDatas( element ) {}
	
	QString status() const
	{ return mDatas.value( "status" ); }
	
	QString emulation() const
	{ return mDatas.value( "emulation" ); }
	
	QString graphic() const
	{ return mDatas.value( "graphic" ); }
	
	QString sound() const
	{ return mDatas.value( "sound" ); }
	
	QString savestate() const
	{ return mDatas.value( "savestate" ); }
	
	QString color() const
	{ return mDatas.value( "color" ); }
	
	QString paletteSize() const
	{ return mDatas.value( "palettesize" ); }
};

/*
<control keydelta="10" reverse="yes" minimum="0" maximum="255" type="paddle" sensitivity="40" />
*/
class iControl : public iGenericDatas
{
public:
	iControl( const QDomElement& element = QDomElement() )
		: iGenericDatas( element ) {}
	
	QString keyDelta() const
	{ return mDatas.value( "keydelta" ); }
	
	QString reverse() const
	{ return mDatas.value( "reverse" ); }
	
	QString minimum() const
	{ return mDatas.value( "minimum" ); }
	
	QString maximum() const
	{ return mDatas.value( "maximum" ); }
	
	QString type() const
	{ return mDatas.value( "type" ); }
	
	QString sensitivity() const
	{ return mDatas.value( "sensitivity" ); }
};

typedef QList<iControl> iControlList;

/*
<input players="4" buttons="3" >
	<control type="joy8way" />
</input>
*/
class iInput : public iGenericDatas
{
public:
		iInput( const QDomElement& element = QDomElement() )
		: iGenericDatas( element )
	{
		const QDomNodeList nodes = element.childNodes();
		
		for ( int i = 0; i < nodes.count(); i++ )
		{
			const QDomElement element = nodes.at( i ).toElement();
			
			mControls << iControl( element );
		}
	}
	
	virtual QString toHtml( int nbspace = 0 ) const
	{
		QString html = iGenericDatas::toHtml( nbspace );
		
		if ( !mControls.isEmpty() )
		{
			html += QString( "<b>Controls</b>:<br />%1" ).arg( iGenericDatas::toHtml( mControls, nbspace ) );
		}
		
		return html;
	}

protected:
	iControlList mControls;
};

/*
<device tag="cart" type="cartridge" mandatory="1" >
	<instance briefname="cart" name="cartridge" />
	<extension name="bin" />
	<extension name="a26" />
</device>
*/
class iDevice : public iGenericDatas
{
public:
		iDevice( const QDomElement& element = QDomElement() )
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
	
	virtual QString toHtml( int nbspace = 0 ) const
	{
		const QString space = QString().fill( ' ', nbspace ).replace( " ", "&nbsp;" );
		QString html = iGenericDatas::toHtml( nbspace );
		
		if ( !mExtensions.isEmpty() )
		{
			html += QString( "%1extension: %2<br />" ).arg( space ).arg( mExtensions.join( ";" ) );
		}
		
		return html;
	}
	
	QString tag() const
	{ return mDatas.value( "tag" ); }
	
	QString type() const
	{ return mDatas.value( "type" ); }
	
	QString mandatory() const
	{ return mDatas.value( "mandatory" ); }
	
	QString briefName() const
	{ return mDatas.value( "briefname" ); }
	
	QString name() const
	{ return mDatas.value( "name" ); }
	
	QStringList extensions() const
	{ return mExtensions; }
	
protected:
	QStringList mExtensions;
};

typedef QList<iDevice> iDeviceList;

/*
<dipvalue default="yes" name="Color" />
*/
class iDipValue : public iGenericDatas
{
public:
	iDipValue( const QDomElement& element = QDomElement() )
		: iGenericDatas( element ) {}
	
	QString _default() const
	{ return mDatas.value( "default" ); }
	
	QString name() const
	{ return mDatas.value( "name" ); }
};

typedef QList<iDipValue> iDipValueList;

/*
<dipswitch name="TV Type" >
	<dipvalue default="yes" name="Color" />
	<dipvalue name="B&amp;W" />
</dipswitch>
*/
class iDipSwitch : public iGenericDatas
{
public:
		iDipSwitch( const QDomElement& element = QDomElement() )
		: iGenericDatas( element )
	{
		const QDomNodeList nodes = element.childNodes();
		
		for ( int i = 0; i < nodes.count(); i++ )
		{
			const QDomElement element = nodes.at( i ).toElement();
			
			mDipValues << iDipValue( element );
		}
	}
	
	virtual QString toHtml( int nbspace = 0 ) const
	{
		QString html = iGenericDatas::toHtml( nbspace );
		
		if ( !mDipValues.isEmpty() )
		{
			html += QString( "<b>DipSwitch</b>:<br />%1" ).arg( iGenericDatas::toHtml( mDipValues, nbspace ) );
		}
		
		return html;
	}
	
	QString name() const
	{ return mDatas.value( "name" ); }

protected:
	iDipValueList mDipValues;
};

typedef QList<iDipSwitch> iDipSwitchList;

class MachineInfos : public iGenericDatas
{
public:
	iBiosList mBios;
	iRomList mRoms;
	iDisplay mDisplay;
	iSound mSound;
	iDriver mDriver;
	iInput mInputs;
	iDeviceList mDevices;
	iDipSwitchList mDipSwitchs;
	
	MachineInfos( const QDomElement& element = QDomElement() )
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
	
	QString name() const
	{ return mDatas.value( "name" ); }
	
	QString cloneOf() const
	{ return mDatas.value( "cloneof" ); }
	
	QString sourceFile() const
	{ return mDatas.value( "sourcefile" ); }
	
	QString description() const
	{ return mDatas.value( "description" ); }
	
	QString year() const
	{ return mDatas.value( "year" ); }
	
	QString manufacturer() const
	{ return mDatas.value( "manufacturer" ); }
	
	virtual QString toHtml( int nbspace = 0 ) const
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
};

class MachineModel;
typedef QList<class MachineItem*> MachineItemList;

class MachineItem
{
public:
	MachineItem( MachineModel* model, const QDomElement& element );
	virtual ~MachineItem();
	
	MachineItem* parent() const;
	void setParent( MachineItem* parent );
	
	MachineItemList children() const;
	MachineItem* child( int row ) const;
	int count() const;
	
	void appendItem( MachineItem* item );
	void removeItem( MachineItem* item );
	void clear();
	
	MachineModel* model() const;
	int row() const;
	
	QString text() const;
	QPixmap icon() const;
	QBrush background() const;
	
	const MachineInfos& infos() const;
	
	static bool lessThan( MachineItem* left, MachineItem* right );
	static void sort( MachineItemList& items );
	
protected:
	MachineModel* mModel;
	MachineInfos mInfos;
	MachineItem* mParent;
	MachineItemList mChildren;
};

#endif // MACHINEITEM_H
