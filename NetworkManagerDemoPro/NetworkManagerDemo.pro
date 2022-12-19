QT       += core gui network widgets charts

greaterThan(QT_MAJOR_VERSION, 4):

TARGET = NetworkManagerDemo
TEMPLATE = app


SOURCES += main.cpp\
        ../qcustomplot/qcustomplot.cpp \
        currencyParser.cpp \
        currencyWidget.cpp \
        qcustomplot.cpp

HEADERS  += \
    ../qcustomplot/qcustomplot.h \
    currencyParser.h \
    currencyWidget.h \
    qcustomplot.h

FORMS    += \
    currencyWidget.ui
