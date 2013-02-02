#include "program_image_widget.h"
#include "ui_program_image_widget.h"

#include "p_gui_virtual_machine.h"

#include <cmath>
#include <iostream>

ProgramImageWidget::ProgramImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramImageWidget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    zoom_scale = 0;
    image_created = false;
}

ProgramImageWidget::~ProgramImageWidget()
{
    delete scene;
    delete ui;
}

void ProgramImageWidget::setPiet(PGuiVirtualMachine *piet)
{
    this->piet = piet;
    image_created = true;
    render();
}

void ProgramImageWidget::render()
{
    scene->clear();
    float zoom_size = getZoomSize();
    const QImage *original = piet->getImage();
    QImage scaled_image = original->scaled(QSize(original->width() * zoom_size, original->height() * zoom_size));
    QPixmap scaled_pixmap = QPixmap::fromImage(scaled_image);
    scene->addPixmap(scaled_pixmap);
    scene->setSceneRect(scene->itemsBoundingRect());
}

float ProgramImageWidget::getZoomSize()
{
    return pow(2.0, zoom_scale);
}

void ProgramImageWidget::zoomIn()
{
    if (image_created)
    {
        zoom_scale++;
        render();
    }
}

void ProgramImageWidget::zoomOut()
{
    if (image_created)
    {
        zoom_scale--;
        render();
    }
}
