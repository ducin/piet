#-------------------------------------------------
#
# Project created by QtCreator 2013-01-25T23:40:41
#
#-------------------------------------------------

QT       += core gui

TARGET = gui
TEMPLATE = app

LIBS += ../../build/src/core/libPietCore.a
INCLUDEPATH += ../core

SOURCES += \
    main.cpp\
    main_window.cpp \
    child_window.cpp \
    machine_widget.cpp \
    program_image_widget.cpp \
    p_gui_virtual_machine.cpp

HEADERS += \
    main_window.h \
    child_window.h \
    machine_widget.h \
    program_image_widget.h \
    p_gui_virtual_machine.h

FORMS += \
    main_window.ui \
    machine_widget.ui \
    program_image_widget.ui

RESOURCES += \
    images.qrc
