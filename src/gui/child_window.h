#ifndef CHILD_WINDOW_H
#define CHILD_WINDOW_H

#include <QtGui>
#include <QWidget>
#include <QMdiSubWindow>

#include "machine_widget.h"

#include "p_virtual_machine.h"

namespace Ui {
    class ChildWindow;
}

class ChildWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit ChildWindow(QWidget *parent = 0);
    ~ChildWindow();

private:
    MachineWidget *machineWidget;
};

#endif // CHILD_WINDOW_H
