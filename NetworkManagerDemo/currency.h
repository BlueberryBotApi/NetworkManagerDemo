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
class Currency: public QObject {
    Q_OBJECT

public:
    explicit Currency(QObject * parent = 0);
    ~Currency();
    QMap <QString,QString> codesOfCurrensy;

public:
    void takeXSDScheme();

private slots:
    QMap<QString,QString> onFinished(QNetworkReply* reply);
signals:
    void QMapIsReady(QMap<QString,QString>);

private:
    QNetworkAccessManager* networkManager;
    QUrl link = QString("http://www.cbr.ru/scripts/XML_val.asp?d=0");
};

#endif // CURRENCY_H
