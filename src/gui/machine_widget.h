#ifndef MACHINE_WIDGET_H
#define MACHINE_WIDGET_H

#include <sstream>

#include <QtGui>
#include <QWidget>

#include "p_gui_virtual_machine.h"
#include "program_image_widget.h"

namespace Ui {
    class MachineWidget;
}

class MachineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MachineWidget(QWidget *parent = 0);
    ~MachineWidget();

    void enableMachineInterface();
    void disableMachineInterface();

signals:
    void fileChosen(QString);

public slots:
    void chooseFile();
    void createMachine(QString);

    void toggleVerbosity(bool);

    void executeSingleInstruction();
    void executeAllInstructions();

    void startMachine();
    void restartMachine();
    void stopMachine();

private:
    Ui::MachineWidget *ui;
    ProgramImageWidget *program_image;

    PGuiVirtualMachine *piet;
    std::stringstream *stream;

    bool machine_created;

    void clearCalcStack();
    void fillCalcStack();
    void updateState();
    void updateInformation();
};

#endif // MACHINE_WIDGET_H
