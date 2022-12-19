QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = NetworkManagerDemo
TEMPLATE = app


SOURCES += main.cpp\
        currencyParser.cpp \
        currencyWidget.cpp \
        qcustomplot.cpp

HEADERS  += \
    currencyParser.h \
    currencyWidget.h \
    qcustomplot.h

FORMS    += \
    currencyWidget.ui
