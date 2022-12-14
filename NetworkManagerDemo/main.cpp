#include "currencyWidget.h"
#include <QApplication>

int main( int argc, char* argv[] ) {

    QApplication a( argc, argv );
    CurrencyWidget w;

    w.show();

    return a.exec();
}
