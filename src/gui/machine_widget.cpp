#include "machine_widget.h"
#include "ui_machine_widget.h"

#include <iostream>
#include <sstream>

#include <QtGui>
#include <QMdiSubWindow>

#include "p_enums.h"
#include "p_structs.h"
#include "p_gui_virtual_machine.h"
#include "program_image_widget.h"

MachineWidget::MachineWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MachineWidget)
{
    ui->setupUi(this);
    connect(this, SIGNAL(fileChosen(QString)), this, SLOT(createMachine(QString)));

    program_image = new ProgramImageWidget();
    ui->groupBoxSource->layout()->addWidget(program_image);
    program_image->show();

    stream = new std::stringstream();

    disableMachineInterface();
    std::cout << "machine widget constructed" << std::endl;
}

MachineWidget::~MachineWidget()
{
    if (machine_created)
    {
        delete piet;
    }
    delete stream;
    delete program_image;
    delete ui;
    std::cout << "machine widget destructed" << std::endl;
}

void MachineWidget::toggleVerbosity(bool verbose)
{
    piet->setVerbosity(verbose);
}

void MachineWidget::chooseFile()
{
  QString filepath = QFileDialog::getOpenFileName(this,
    tr("Open File"), "", tr("Files (*.*)"));

  if (!filepath.isEmpty()) {
    QImage *image = new QImage(filepath);
    if (image->isNull()) {
      QMessageBox::information(this, tr(
        "Image Viewer"), tr("Cannot load %1.").arg(filepath));
      return;
    } else {
        emit fileChosen(filepath);
    }
  }
}

void MachineWidget::createMachine(QString filepath)
{
    this->setWindowTitle(filepath);
    ui->consoleOutputBrowser->setText("");

    if (machine_created)
    {
      delete piet;
    }

    piet = new PGuiVirtualMachine(filepath.toStdString().c_str(), *stream);
    program_image->setPiet(piet);
    program_image->render();
    machine_created = true;
    updateInformation();
}

///////////////////////////////////////////////////////////////////////////////

void MachineWidget::enableMachineInterface()
{
    machine_created = true;
    ui->pushButtonExecuteAllInstructions->setEnabled(true);
    ui->pushButtonExecuteSingleInstruction->setEnabled(true);
    ui->pushButtonStop->setEnabled(true);
}

void MachineWidget::disableMachineInterface()
{
    machine_created = false;
    ui->pushButtonExecuteAllInstructions->setEnabled(false);
    ui->pushButtonExecuteSingleInstruction->setEnabled(false);
    ui->pushButtonStop->setEnabled(false);
}

void MachineWidget::executeSingleInstruction()
{
    piet->executeSingleInstr();
    std::string output(stream->str());
    stream->str(""); // clearing
    ui->consoleOutputBrowser->setText(ui->consoleOutputBrowser->toPlainText().append(output.c_str()));
    updateInformation();
}

void MachineWidget::executeAllInstructions()
{
    piet->executeAllInstr();
    std::string output(stream->str());
    stream->str(""); // clearing
    ui->consoleOutputBrowser->setText(ui->consoleOutputBrowser->toPlainText().append(output.c_str()));
    updateInformation();
}

void MachineWidget::startMachine()
{
    piet->startMachine();
    std::cout << "STARTED" << std::endl;
    enableMachineInterface();
    updateCodeCoordinates();
    updateState();
}

void MachineWidget::restartMachine()
{
    piet->restartMachine();
    updateState();
}

void MachineWidget::stopMachine()
{
    piet->stopMachine();
    disableMachineInterface();
    updateState();
}

void MachineWidget::clearCalcStack()
{
    while(ui->listWidgetCalcStack->count())
        ui->listWidgetCalcStack->takeItem(0);
}

void MachineWidget::fillCalcStack()
{
    for (std::list<int>::iterator it = piet->calc_stack_begin_iterator(); it != piet->calc_stack_end_iterator(); ++it)
        ui->listWidgetCalcStack->addItem(QString::number(*it));
}

void MachineWidget::updateState()
{
    PMachineStates state = piet->getState();
    ui->labelStateValue->setText(PEnums::machineState(state));
    if (state == state_finished) {
        ui->pushButtonExecuteAllInstructions->setEnabled(false);
        ui->pushButtonExecuteSingleInstruction->setEnabled(false);
    }
}

void MachineWidget::updateCodeCoordinates()
{
    PPoint coords = piet->getCodePointerCoordinates();
    ui->labelPointerXValue->setText(QString::number(coords.x));
    ui->labelPointerYValue->setText(QString::number(coords.y));

    PCodelChooserValues cc = piet->getCodelChooser();
    ui->labelPointerCCValue->setText(PEnums::codelChooser(cc));

    PDirectionPointerValues dp = piet->getDirectionPointer();
    ui->labelPointerDPValue->setText(PEnums::directionPointer(dp));
}

void MachineWidget::updateInformation()
{
    clearCalcStack();
    fillCalcStack();
    updateState();
    updateCodeCoordinates();
}
