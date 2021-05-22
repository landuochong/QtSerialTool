#-------------------------------------------------
#
# Project created by QtCreator 2021-05-22T11:18:35
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialTest
TEMPLATE = app


SOURCES += main.cpp\
        SerialWidget.cpp

HEADERS  += SerialWidget.h

FORMS    += serialwidget.ui
