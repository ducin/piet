#ifndef AUTHOR_H
#define AUTHOR_H

#include <QDialog>
#include <QSlider>
#include <QLabel>

#include "WorkspaceWindow.h"
#include "ui_Author.h"

class AuthorWidget : public QDialog, Ui_AuthorDialog
{
	Q_OBJECT

	private:

		QSize sizeHint() const;
		QSize minimumSize() const;
		QSize maximumSize() const;

	public:

		AuthorWidget(QWidget *parent);
};

#endif
