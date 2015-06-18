#-------------------------------------------------
#
# Project created by QtCreator 2015-05-24T11:12:24
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_LAB4_CHULL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    convexhullengine.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    convexhullengine.h

FORMS    += mainwindow.ui
