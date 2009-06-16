#ifndef UIABOUT_H
#define UIABOUT_H

#include "ui_UIAbout.h"

class UIAbout : public QDialog, public Ui::UIAbout
{
	Q_OBJECT

public:
	UIAbout( QWidget* parent = 0 );
	virtual ~UIAbout();

protected:
	virtual bool eventFilter( QObject* object, QEvent* event );
};

#endif // UIABOUT_H
