#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T16:14:58
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_LAB5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    splineengine.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    splineengine.h

FORMS    += mainwindow.ui
