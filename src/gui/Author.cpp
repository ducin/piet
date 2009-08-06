#include <QtGui>

#include "Author.h"

AuthorWidget::AuthorWidget(QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	setWindowTitle(QString("autor programu"));
}

QSize AuthorWidget::sizeHint() const
{
	return QSize(300, 120);
}

QSize AuthorWidget::minimumSize() const
{
	return QSize(300, 120);
}

QSize AuthorWidget::maximumSize() const
{
	return QSize(300, 120);
}

/*=====================================================================*/
