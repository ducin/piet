#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QList>

#include "child_window.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openChildWindow();
    void displayAbout();

private:
    Ui::MainWindow *ui;
    ChildWindow *childWindow;
};

#endif // MAIN_WINDOW_H
