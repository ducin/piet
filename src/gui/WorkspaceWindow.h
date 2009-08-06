#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QtGui>
#include "ui_WorkspaceWindow.h"

/**********************************************/

class WorkspaceWindow : public QMainWindow, Ui::WorkspaceWindow
{
	Q_OBJECT
	
	public:

		WorkspaceWindow(QWidget *parent = 0);
		void setStatusMessage(const QString &);

	private:

		QWorkspace *workspace;
		QStatusBar *status;

//-------------------------------------------

	public slots:

//-------------------------------------------

	private slots:

		void sWindowActivated(QWidget *window);
		
		void sOpen();
		void sSave();
		void sQuit();
		void sAuthor();

//-------------------------------------------

};

#endif
