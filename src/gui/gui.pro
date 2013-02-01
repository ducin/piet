#-------------------------------------------------
#
# Project created by QtCreator 2013-01-25T23:40:41
#
#-------------------------------------------------

QT       += core gui

TARGET = gui
TEMPLATE = app

LIBS += ./../../build/src/core/libPietCore.a
INCLUDEPATH += ./../core

SOURCES += \
    main.cpp\
    main_window.cpp \
    child_window.cpp \
    machine_widget.cpp \
    pguivirtualmachine.cpp

HEADERS += \
    main_window.h \
    child_window.h \
    machine_widget.h \
    pguivirtualmachine.h

FORMS += \
    main_window.ui \
    machine_widget.ui

RESOURCES += \
    application.qrc
