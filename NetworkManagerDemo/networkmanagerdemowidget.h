#ifndef NETWORKMANAGERDEMOWIDGET_H
#define NETWORKMANAGERDEMOWIDGET_H

#include "currency.h"


namespace Ui {
class NetworkManagerDemoWidget;
}

class NetworkManagerDemoWidget : public QWidget {
    Q_OBJECT

public:
    explicit NetworkManagerDemoWidget( QWidget* parent = 0 );
    ~NetworkManagerDemoWidget();

private slots:
    void onGo();
    void onFinished( QNetworkReply* reply );

private:
    Currency* ForCodesANDCurrecyNames;
    Ui::NetworkManagerDemoWidget* ui;
    QString ForOneCheck = "http://www.cbr.ru/scripts/XML_daily.asp?date_req=";
    QNetworkAccessManager m_manager;

};


#endif // NETWORKMANAGERDEMOWIDGET_H
