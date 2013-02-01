#include "machine_widget.h"
#include "ui_machine_widget.h"

#include <iostream>
#include <sstream>

#include <QMdiSubWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "penums.h"
#include "pguivirtualmachine.h"

MachineWidget::MachineWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MachineWidget)
{
  ui->setupUi(this);
  disableMachineInterface();
  stream = new std::stringstream();
  std::cout << "machine widget constructed" << std::endl;
}

MachineWidget::~MachineWidget()
{
    delete ui;
    if (machine_created)
    {
        delete piet;
        delete image;
    }
    delete stream;
    std::cout << "machine widget destructed" << std::endl;
}

void MachineWidget::toggleVerbosity(bool verbose)
{
  piet->setVerbosity(verbose);
}

void MachineWidget::chooseFile()
{
  filepath = QFileDialog::getOpenFileName(this,
    tr("Open File"), "", tr("Files (*.*)"));

  if (!filepath.isEmpty()) {
    QImage *image = new QImage(filepath);
    if (image->isNull()) {
      QMessageBox::information(this, tr(
        "Image Viewer"), tr("Cannot load %1.").arg(filepath));
      return;
    } else {
        createMachine(image);
    }
  }
}

unsigned char MachineWidget::getZoomSize()
{
    unsigned char zoom_size = 1;
    for (int i = 0; i < zoom_scale; i++)
        zoom_size *= 2;
    return zoom_size;
}

void MachineWidget::zoomIn()
{
    if (machine_created)
    {
        zoom_scale++;
        unsigned char zoom_size = getZoomSize();
        QImage scaled_image = image->scaled(QSize(image->width() * zoom_size, image->height() * zoom_size));
        QPixmap scaled_pixmap = QPixmap::fromImage(scaled_image);
        QGraphicsScene *scene = ui->graphicsView->scene();
        scene->clear();
        scene->addPixmap(scaled_pixmap);
    }
}

void MachineWidget::zoomOut()
{

}

void MachineWidget::createMachine(QImage *image)
{
  QPixmap pixmap = QPixmap::fromImage(*image);
  scene = new QGraphicsScene(this);
  scene->addPixmap(pixmap);
  ui->graphicsView->setScene(scene);
//  ui->graphicsView->setGeometry(20, 20, image.width() + 50, image.height() + 50);
  this->setWindowTitle(filepath);
  ui->consoleOutputBrowser->setText("");

  if (machine_created)
  {
    delete piet;
    delete this->image;
  }

  // store the reference to the QImage
  this->image = image;
  zoom_scale = 0;
  piet = new PGuiVirtualMachine(filepath, *stream);
  machine_created = true;
  updateInformation();
}

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
    switch (state)
    {
    case state_ready:
        ui->labelStateValue->setText("Ready");
        break;
    case state_running:
        ui->labelStateValue->setText("Running");
        break;
    case state_finished:
        ui->labelStateValue->setText("Finished");
        break;
    }
}

void MachineWidget::updateInformation()
{
    clearCalcStack();
    fillCalcStack();
    updateState();
}
