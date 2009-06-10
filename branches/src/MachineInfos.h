#ifndef MACHINEINFOS_H
#define MACHINEINFOS_H

#include <QDomElement>
#include <QMap>
#include <QStringList>

// iGenericDatas

class iGenericDatas
{
public:
	iGenericDatas( const QDomElement& element = QDomElement() );
	
	virtual QString toHtml( int nbspace = 0 ) const;
	
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
	
	QMap<QString, QString> datas() const;
	QString data( const QString& key ) const;

protected:
	QMap<QString, QString> mDatas;
};

// iBios

class iBios : public iGenericDatas
{
public:
	enum Type
	{
		Default,
		Description,
		Name
	};
	
	iBios( const QDomElement& element = QDomElement() );
	
	QString data( iBios::Type type ) const;
};

typedef QList<iBios> iBiosList;

// iRom

class iRom : public iGenericDatas
{
public:
	enum Type
	{
		Status,
		Offset,
		Size,
		Region,
		Sha1,
		Bios,
		Name,
		Crc
	};
	
	iRom( const QDomElement& element = QDomElement() );
	
	QString data( iRom::Type type ) const;
};

typedef QList<iRom> iRomList;

// iChip

class iChip : public iGenericDatas
{
public:
	enum Type
	{
		Tag,
		Clock,
		Cpu,
		Name
	};
	
	iChip( const QDomElement& element = QDomElement() );
	
	QString data( iChip::Type type ) const;
};

typedef QList<iChip> iChipList;

// idisplay

class iDisplay : public iGenericDatas
{
public:
	enum Type
	{
		Width,
		Height,
		PixClock,
		VBStart,
		VBEnd,
		_Type,
		HTotal,
		VTotal,
		HBStart,
		HBEnd,
		Rotate,
		Refresh
	};
	
	iDisplay( const QDomElement& element = QDomElement() );
	
	QString data( iDisplay::Type type ) const;
};

// iSound

class iSound : public iGenericDatas
{
public:
	enum Type
	{
		Channels
	};
	
	iSound( const QDomElement& element = QDomElement() );
	
	QString data( iSound::Type type ) const;
};

// iDriver

class iDriver : public iGenericDatas
{
public:
	enum Type
	{
		Status,
		Emulation,
		Graphic,
		Sound,
		SaveState,
		Color,
		PaletteSize
	};
	
	iDriver( const QDomElement& element = QDomElement() );
	
	QString data( iDriver::Type type ) const;
};

// iControl

class iControl : public iGenericDatas
{
public:
	enum Type
	{
		KeyDelta,
		Reverse,
		Minimum,
		Maximum,
		_Type,
		Sensitivity
	};
	
	iControl( const QDomElement& element = QDomElement() );
	
	QString data( iControl::Type type ) const;
};

typedef QList<iControl> iControlList;

// iInput

class iInput : public iGenericDatas
{
public:
	iInput( const QDomElement& element = QDomElement() );
	
	virtual QString toHtml( int nbspace = 0 ) const;
	
	iControlList controls() const;

protected:
	iControlList mControls;
};

// iDevice

class iDevice : public iGenericDatas
{
public:
	enum Type
	{
		Tag,
		_Type,
		Mandatory,
		BriefName,
		Name
	};
	
	iDevice( const QDomElement& element = QDomElement() );
	
	virtual QString toHtml( int nbspace = 0 ) const;
	
	QString data( iDevice::Type type ) const;
	
	QStringList extensions() const;
	
protected:
	QStringList mExtensions;
};

typedef QList<iDevice> iDeviceList;

// iDipValue

class iDipValue : public iGenericDatas
{
public:
	enum Type
	{
		Default,
		Name
	};
	
	iDipValue( const QDomElement& element = QDomElement() );
	
	QString data( iDipValue::Type type ) const;
};

typedef QList<iDipValue> iDipValueList;

// iDipSwitch

class iDipSwitch : public iGenericDatas
{
public:
	enum Type
	{
		Name
	};
	
	iDipSwitch( const QDomElement& element = QDomElement() );
	
	virtual QString toHtml( int nbspace = 0 ) const;
	
	QString data( iDipSwitch::Type type ) const;
	
	iDipValueList dipValues() const;

protected:
	iDipValueList mDipValues;
};

typedef QList<iDipSwitch> iDipSwitchList;

// MachineInfos

class MachineInfos : public iGenericDatas
{
public:
	enum Type
	{
		Name,
		CloneOf,
		SourceFile,
		Description,
		Year,
		Manufacturer
	};
	
	MachineInfos( const QDomElement& element = QDomElement() );
	
	virtual QString toHtml( int nbspace = 0 ) const;
	
	QString data( MachineInfos::Type type ) const;
	
	iBiosList bios() const;
	iRomList roms() const;
	iDisplay display() const;
	iSound sound() const;
	iDriver driver() const;
	iInput inputs() const;
	iDeviceList devices() const;
	iDipSwitchList dipSwitchs() const;
	
protected:
	iBiosList mBios;
	iRomList mRoms;
	iDisplay mDisplay;
	iSound mSound;
	iDriver mDriver;
	iInput mInputs;
	iDeviceList mDevices;
	iDipSwitchList mDipSwitchs;
};

#endif // MACHINEINFOS_H
