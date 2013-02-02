#ifndef PROGRAM_IMAGE_WIDGET_H
#define PROGRAM_IMAGE_WIDGET_H

#include <QtGui>
#include <QImage>
#include <QString>
#include <QWidget>

#include "p_gui_virtual_machine.h"

namespace Ui {
    class ProgramImageWidget;
}

class ProgramImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramImageWidget(QWidget *parent = 0);
    ~ProgramImageWidget();

    void setPiet(PGuiVirtualMachine *);
    void render();

private:
    float getZoomSize();
    PGuiVirtualMachine *piet;

public slots:
    void zoomIn();
    void zoomOut();

private:
    Ui::ProgramImageWidget *ui;

    bool image_created;

    QGraphicsScene *scene;
    signed char zoom_scale;
};

#endif // PROGRAM_IMAGE_WIDGET_H
