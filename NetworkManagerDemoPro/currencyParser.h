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
    explicit CurrencyParser(QObject* parent = nullptr);
    ~CurrencyParser();
    QMap <QString,QString> currencyCodes;
    QMap <QDate,QString> quoteByDate;

public:
    void sendCurrencyRequest();
    void sendQuoteRequest(const QString &startDateOfvalue,const QString &endDateOfvalue,const QString &nameOfCurrency);

private:
    QString xmlToString(QByteArray xml);

private slots:
    void onCurrencyRequestFinished(const QString &string);
    void onQuoteRequestFinished(const QString &string);
    void switchBlock (QNetworkReply* reply);

signals:
    void CurrencyIsReady(QMap<QString,QString>);
    void QuoteIsReady(QMap<QDate,QString>);
    void Quote(QString);
    void CodesOfCurrency(QString);

private:
    QNetworkAccessManager* pNetworkManager;
    QString linkCurrency = "http://www.cbr.ru/scripts/XML_val.asp?d=0";
    QString linkQuotePrefix = "http://www.cbr.ru/scripts/XML_dynamic.asp?";
};

#endif // CURRENCYPARSER_H
