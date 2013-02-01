#include "main_window.h"
#include "ui_main_window.h"

#include "child_window.h"

#include <QList>
#include <QMdiArea>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::displayAbout()
{
  QMessageBox::about(this, tr("About Piet Esoteric Language Interpreter"),
    tr("<p><a href='http://en.wikipedia.org/wiki/Piet_(programming_language)'>Piet</a> "
      "is a graphical programming language designed by "
      "<a href='http://en.wikipedia.org/wiki/David_Morgan-Mar'>David Morgan-Mar</a>. "
      "Read more about Piet at "
      "<a href='http://www.dangermouse.net/esoteric/piet.html'>author's page</a> "
      "This non-commercial project is a Piet GUI interpreter designed by Tomasz Ducin. "
      "For more information visit "
      "<a href='https://github.com/tkoomzaaskz/piet'>github piet project</a>.</p>"
      "<p>&copy; 2009-2013 Tomasz Ducin</p>"));
}

void MainWindow::openChildWindow()
{
  childWindow = new ChildWindow(ui->mdiArea);
  childWindow->setAttribute(Qt::WA_DeleteOnClose);
  childWindow->show();
}
