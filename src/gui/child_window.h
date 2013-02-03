#ifndef CHILD_WINDOW_H
#define CHILD_WINDOW_H

#include "machine_widget.h"

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
