#ifndef MACHINE_WIDGET_H
#define MACHINE_WIDGET_H

#include <sstream>

#include <QtGui>
#include <QImage>
#include <QWidget>

#include "pguivirtualmachine.h"

namespace Ui {
    class MachineWidget;
}

class MachineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MachineWidget(QWidget *parent = 0);
    ~MachineWidget();

    void createMachine(QImage *);
    void enableMachineInterface();
    void disableMachineInterface();

public slots:
    void chooseFile();
    void toggleVerbosity(bool);

    void zoomIn();
    void zoomOut();

    void executeSingleInstruction();
    void executeAllInstructions();

    void startMachine();
    void restartMachine();
    void stopMachine();

private:
    Ui::MachineWidget *ui;

    QString filepath;
    QGraphicsScene *scene;

    signed char zoom_scale;
    QImage *image;

    PGuiVirtualMachine *piet;
    bool machine_created;

    std::stringstream *stream;

    unsigned char getZoomSize();

    void clearCalcStack();
    void fillCalcStack();
    void updateState();
    void updateInformation();
};

#endif // MACHINE_WIDGET_H
