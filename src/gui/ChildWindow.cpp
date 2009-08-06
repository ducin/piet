//// incudes

// GUI
#include "ChildWindow.h"

// Qt
#include <QtGui>

// C++
#include <iostream>

/**********************************************/

ChildWindow *ChildWindow::_recent = NULL;

/**********************************************/

ChildWindow::ChildWindow(QWidget *parent, const QString &title, QImage *img): QWidget(parent)
{
	setWindowTitle(title);
	
	_scroll = new QScrollArea(NULL);

	// _canvas = new DImageWidget(img);
	// _scroll->setWidget(_canvas);

	_scroll->viewport()->setBackgroundRole(QPalette::Background);
	_scroll->viewport()->setAutoFillBackground(true);
	_scroll->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(_scroll);
	layout->setMargin(1);
	layout->setSpacing(1);
	setLayout(layout);
	
	setFocusPolicy(Qt::ClickFocus);
}

/**********************************************/

void ChildWindow::setAsRecent()
{
	_recent = this;
}
