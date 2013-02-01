#include "child_window.h"

#include <QMdiSubWindow>

#include "machine_widget.h"

ChildWindow::ChildWindow(QWidget *parent) :
  QMdiSubWindow(parent)
{
    machineWidget = new MachineWidget(this);
    //machineWidget->show();
    this->setWidget(machineWidget);

}

ChildWindow::~ChildWindow()
{
    machineWidget->~MachineWidget();
}
