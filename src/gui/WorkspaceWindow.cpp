////includes

// GUI
#include "ChildWindow.h"
#include "WorkspaceWindow.h"

#include "Author.h"

// Qt
#include <QtGui>

// C++
#include <iostream>
using namespace std;

/****************************************************/

WorkspaceWindow::WorkspaceWindow(QWidget *parent): QMainWindow(parent), Ui::WorkspaceWindow()
{
	setupUi(this);
	
	workspace = new QWorkspace(this);
	setCentralWidget(workspace);
	
	connect(workspace,       SIGNAL(windowActivated(QWidget*)), this, SLOT(sWindowActivated(QWidget*)));

	connect(aOpen,           SIGNAL(triggered()), this,  SLOT(sOpen()));
	connect(aSaveAs,         SIGNAL(triggered()), this,  SLOT(sSave()));
	connect(aExit,           SIGNAL(triggered()), this,  SLOT(sQuit()));

	connect(aAuthor,         SIGNAL(triggered()), this,  SLOT(sAuthor()));

//--------------------------------------------------------

	setWindowTitle("Piet project: interpreter");
	setStatusBar(status = new QStatusBar());
}

/****************************************************/

void WorkspaceWindow::sWindowActivated(QWidget *window)
{
	ChildWindow *cw = (ChildWindow*)window;
	cw->setAsRecent();
}

/****************************************************/

void WorkspaceWindow::sQuit()
{
	this->close();
}

/****************************************************/

void WorkspaceWindow::sOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this, "open image", ".", "formats (*.jpg *.png *.bmp)\n" "all formats (*.*)");
	if (!fileName.isEmpty())
	{
		QImage *img = new QImage(fileName);
		if (img->isNull())
		{
			delete img;
			QMessageBox::critical(this, "error", "File format not recognized:\n " + fileName, QMessageBox::Ok | QMessageBox::Default);
		}
		else
		{
			QImage *real;
			if (img->format() != QImage::Format_ARGB32)
			{
				real = new QImage(img->size(), QImage::Format_ARGB32);
				QPainter p(real);
				p.drawImage(0, 0, *img);
				delete img;
			}
			else
			{
				real = img;
			}
			ChildWindow *cw = new ChildWindow(NULL, fileName, real);
			workspace->addWindow(cw);
			cw->show();
			status->showMessage("wczytano plik " + fileName);
		}
	}
}

/****************************************************/

void WorkspaceWindow::sSave()
{
	ChildWindow *cw = ChildWindow::recent();
	if (!cw)
		return;
	QString fileName = QFileDialog::getSaveFileName(this, "Zapisz obrazek jako...", cw->windowTitle(), "Obrazek PNG (*.png)");

	if (!fileName.isEmpty())
	if (!cw)//->canvas()->bitmap->save(fileName, "png"))
		QMessageBox::critical(this, "Niepowodzenie", "Nie udalo sie zapisac obrazka pod wskazana nazwa:\n " + fileName, QMessageBox::Ok | QMessageBox::Default);      	
	else
		cw->setWindowTitle(fileName);
}

void WorkspaceWindow::setStatusMessage(const QString &message)
{
	this->status->showMessage(message);
}

/***********************************************************************************/

void WorkspaceWindow::sAuthor()
{
	AuthorWidget *author_widget = new AuthorWidget(this);
	author_widget->show();
}
