

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkManagerDemo
TEMPLATE = app


SOURCES += main.cpp\
        networkmanagerdemowidget.cpp

HEADERS  += networkmanagerdemowidget.h

FORMS    += networkmanagerdemowidget.ui
