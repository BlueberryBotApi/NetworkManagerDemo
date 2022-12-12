#ifndef CURRENCY_H
#define CURRENCY_H


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
class Currency: public QWidget{
    Q_OBJECT

public:
    explicit Currency(QWidget* parent = 0);
    ~Currency();
    QMap <QString,QString> codesOfCurrensy;

public:
    QStringList takeXSDScheme();

private slots:
    void onFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* networkManager;
    QUrl link = QString("http://www.cbr.ru/scripts/XML_val.asp?d=0");
};

#endif // CURRENCY_H
