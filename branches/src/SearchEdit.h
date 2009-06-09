#ifndef SEARCHEDIT_WIN_H
#define SEARCHEDIT_WIN_H

#include <QLineEdit>

class QToolButton;
class QTimer;

class SearchEdit : public QLineEdit
{
	Q_OBJECT
	
public:
	SearchEdit( QWidget* parent, const QString& promptText = QString::null );

	QSize sizeHint() const;
	void setMenu( QMenu* menu );

protected:
	bool mShowPrompt;
	QString mTextPrompt;
	QToolButton* mOptionsButton;
	QToolButton* mClearButton;
	QTimer* mTimer;

	void resizeEvent( QResizeEvent* e );
	void focusInEvent( QFocusEvent* e );
	void focusOutEvent( QFocusEvent* e );
	void paintEvent( QPaintEvent* e );

public slots:
	void showPrompt( bool show );
	void setPromptText( const QString& text );

protected slots:
	void updateCloseButton( const QString& text );
	void timer_timeout();

signals:
	void searchChanged( const QString& text );
};

#endif // SEARCHEDIT_WIN_H
