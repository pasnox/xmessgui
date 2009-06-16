/****************************************************************************
**
** 		Created using Monkey Studio v1.8.3.3
** Authors   : AZEVEDO Filipe aka Nox P@sNox - pasnox@gmail.com
** Project   : xMess Gui
** FileName  : RomModel.h
** Date      : 2009-06-16T18:56:53
** License   : GPL v3
** Comment   : Free, Fast & Powerfull (sdl)mess front end.
** Home Page : http://xmessgui.googlecode.com
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef ROMMODEL_H
#define ROMMODEL_H

#include <QAbstractItemModel>
#include <QFileInfo>

class RomModelThread;
class MachineItem;
class Settings;

class RomModel : public QAbstractItemModel
{
	Q_OBJECT
	
public:
	RomModel( QObject* parent );
	virtual ~RomModel();
	
	virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
	virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
	virtual QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const;
	virtual QModelIndex parent( const QModelIndex& index ) const;
	virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
	virtual bool hasChildren( const QModelIndex& parent = QModelIndex() ) const;
	
	QString filePath( const QModelIndex& index ) const;

public slots:
	void refresh( const MachineItem* machine, const Settings* settings, const QString& searchWildcard );

protected:
	RomModelThread* mThread;
	QIcon* mIcon;
	QFileInfoList mFiles;

protected slots:
	void queryFinished( const QFileInfoList& files );

signals:
	void ready();
};

#endif // ROMMODEL_H
