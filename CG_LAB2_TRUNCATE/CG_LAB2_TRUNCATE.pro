#-------------------------------------------------
#
# Project created by QtCreator 2015-05-06T21:02:04
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_LAB2_TRUNCATE
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    truncater.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    truncater.h

FORMS    += mainwindow.ui
