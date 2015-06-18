#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T21:40:08
#
#-------------------------------------------------

QT += core gui
QT += opengl

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_LAB1_2DDerevo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawcanvas.cpp \
    d2tree.cpp

HEADERS  += mainwindow.h \
    drawcanvas.h \
    d2tree.h

FORMS    += mainwindow.ui
