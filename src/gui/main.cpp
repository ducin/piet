#include <QtGui/QApplication>
#include "main_window.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Tomasz Ducin");
    app.setApplicationName("Application Example");
    MainWindow w;
    w.show();

    return app.exec();
}
