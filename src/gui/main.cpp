#include <QtGui/QApplication>
#include "main_window.h"

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "P GUI VM - virtual method: jak sięzmienia stan, niech VM wysyła sygnał, który złapie machine widget" << std::endl;

    QApplication app(argc, argv);
    app.setOrganizationName("Tomasz Ducin");
    app.setApplicationName("Application Example");
    MainWindow w;
    w.show();

    return app.exec();
}
