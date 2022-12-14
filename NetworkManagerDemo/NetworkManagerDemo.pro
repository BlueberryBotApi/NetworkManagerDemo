QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkManagerDemo
TEMPLATE = app


SOURCES += main.cpp\
        currencyParser.cpp \
        currencyWidget.cpp

HEADERS  += \
    currencyParser.h \
    currencyWidget.h

FORMS    += \
    currencyWidget.ui
