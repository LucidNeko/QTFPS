#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T15:56:01
#
#-------------------------------------------------

QT       += core gui

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTFPS
TEMPLATE = app


SOURCES += main.cpp\
    glview.cpp \
    tiny_obj_loader.cpp \
    mesh.cpp

HEADERS  += \
    glview.h \
    tiny_obj_loader.h \
    meshloader.h \
    mesh.h

RESOURCES += \
    resources.qrc
