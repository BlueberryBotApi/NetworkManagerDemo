#ifndef CURRENCYPARSER_H
#define CURRENCYPARSER_H


#include <QMap>
#include <QWidget>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QXmlStreamReader>
#include <QTextCodec>
#include <QDateTime>
#include <QStringList>
class CurrencyParser: public QObject {
    Q_OBJECT

public:
    explicit CurrencyParser(QObject* parent = 0);
    ~CurrencyParser();
    QMap <QString,QString> currencyCodes;
    QMap <QString,QString> quoteByDate;

public:
    void sendCurrencyRequest();
    void sendQuoteRequest(QString startDateOfvalue, QString endDateOfvalue, QString nameOfCurrency);

private:
    QString xmlToString(QByteArray xml);

private slots:
    void onCurrencyRequestFinished(QNetworkReply* reply);
    void onQuoteRequestFinished(QNetworkReply* reply);

signals:
    void CurrencyIsReady(QMap<QString,QString>);
    void QuoteIsReady(QMap<QString,QString>);

private:
    QNetworkAccessManager* pNetworkManager;
    QString linkCurrency = "http://www.cbr.ru/scripts/XML_val.asp?d=0";
    QString linkQuotePrefix = "http://www.cbr.ru/scripts/XML_dynamic.asp?";
};

#endif // CURRENCYPARSER_H
