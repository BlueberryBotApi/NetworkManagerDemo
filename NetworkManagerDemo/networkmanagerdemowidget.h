#ifndef NETWORKMANAGERDEMOWIDGET_H
#define NETWORKMANAGERDEMOWIDGET_H


#include <QWidget>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
//#include <QDebug>
//#include <QXmlStreamReader>
#include <QTextCodec>
#include <QDateTime>

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
    Ui::NetworkManagerDemoWidget* ui;
    QString ForOneCheck = "http://www.cbr.ru/scripts/XML_daily.asp?date_req=";
    QNetworkAccessManager m_manager;

};

#endif // NETWORKMANAGERDEMOWIDGET_H
