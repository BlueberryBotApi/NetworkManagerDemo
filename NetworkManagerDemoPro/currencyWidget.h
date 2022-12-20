#ifndef CURRENCYWIDGET_H
#define CURRENCYWIDGET_H

#include "currencyParser.h"
#include "qcustomplot.h"

// should see this change in git

namespace Ui {
class CurrencyWidget;
}

class CurrencyWidget : public QWidget {
    Q_OBJECT

public:
    explicit CurrencyWidget(QWidget* parent = nullptr);
    ~CurrencyWidget();

private:
    void makeComboBox();

private slots:
    void onGo();
    void onQuoteMapIsReady(QMap<QDate,QString> map);
    void onCurrencyMapIsReady(QMap<QString,QString> map);
    void makeTable();

private:
    QMap <QString,QString> currencyCodes;
    QMap <QDate,QString> quoteByDate; // quote = котировка
    CurrencyParser* pCurrencyParser;
    Ui::CurrencyWidget* ui;
    QString linkPrefix = "http://www.cbr.ru/scripts/XML_dynamic.asp?";
    QNetworkAccessManager networkManager;
};


#endif // CURRENCYWIDGET_H
