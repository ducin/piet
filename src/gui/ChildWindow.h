#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

// Qt
#include <QWidget>
class QScrollArea;

/**********************************************/

class ChildWindow : public QWidget
{
	Q_OBJECT
	
	private:
		QScrollArea *_scroll;
//		DImageWidget *_canvas;
		
		static ChildWindow *_recent;

	public:

		ChildWindow(QWidget *parent, const QString& title, QImage *img);
//		DImageWidget *canvas() {return _canvas;};
		static ChildWindow *recent() { return _recent; };
		
	public slots:

		void setAsRecent();
};

/**********************************************/

#endif
