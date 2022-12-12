QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkManagerDemo
TEMPLATE = app


SOURCES += main.cpp\
        currency.cpp \
        networkmanagerdemowidget.cpp

HEADERS  += networkmanagerdemowidget.h \
    currency.h

FORMS    += networkmanagerdemowidget.ui
