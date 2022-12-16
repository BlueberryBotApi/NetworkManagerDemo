#include "currencyParser.h"

CurrencyParser::CurrencyParser(QObject* parent)
    : QObject {parent}
{

    this->pNetworkManager = new QNetworkAccessManager();

}
CurrencyParser::~CurrencyParser()
{
    delete this->pNetworkManager;
}

void CurrencyParser::sendCurrencyRequest()
{
    connect( this->pNetworkManager, SIGNAL(finished(QNetworkReply*)), SLOT(onCurrencyRequestFinished(QNetworkReply*)) );

    pNetworkManager->get(QNetworkRequest(this->linkCurrency));
}

void CurrencyParser::onCurrencyRequestFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        emit CurrencyIsReady(currencyCodes);
        //this->pNetworkManager->deleteLater();
        return ;
    }

    QString string = xmlToString(reply->readAll());

    int i = 0, j = 0;
    QString name;
    QString buf;
    while (i != -1)
    {
        buf="";
        i = string.indexOf("Name", j);
        if (i != -1)
        {
            i += 5;
            while (string[i] != '<')
            {
                buf += string[i];
                i++;
            }
            j = i;
            name = buf;
            buf = "";
            i = string.indexOf("ParentCode", j);
            i += 11;
            while (string[i] != ' ')
            {
                buf += string[i];
                i++;
            }
            this->currencyCodes[name]=buf;
            j = i;
        }
    }

    reply->deleteLater();

    disconnect(this->pNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onCurrencyRequestFinished(QNetworkReply*)) );

    emit CurrencyIsReady(currencyCodes);
}

void CurrencyParser::sendQuoteRequest(const QString &startDateOfvalue,const QString &endDateOfvalue,const QString &nameOfCurrency)
{
    connect( this->pNetworkManager, SIGNAL(finished(QNetworkReply*)), SLOT(onQuoteRequestFinished(QNetworkReply*)) );

    this->pNetworkManager->get(QNetworkRequest(QUrl(this->linkQuotePrefix +
                                            "date_req1=" + startDateOfvalue +
                                            "&date_req2=" + endDateOfvalue +
                                            "&VAL_NM_RQ=" + this->currencyCodes[nameOfCurrency])));
}

void CurrencyParser::onQuoteRequestFinished(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return ;
    }

        QString string = xmlToString(reply->readAll());

        QString buf;
        QDate date;
        int i = 0, j = 0;
        while (i != -1)
        {
            buf="";
            i = string.indexOf("Record Date", j);
            if(i != -1)
            {
                i += 13;
                while (string[i] != '"')
                {
                    buf += string[i];
                    i++;
                }
                j = i;
                date = date.fromString(buf,"dd.MM.yyyy");
                buf = "";
                i = string.indexOf("Value", j);
                i += 6;
                while (string[i] != '<')
                {
                    buf += string[i];
                    i++;
                }
                this->quoteByDate[date] = buf;
                j = i;
            }
        }

    reply->deleteLater();

    disconnect(this->pNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onQuoteRequestFinished(QNetworkReply*)) );

    emit QuoteIsReady(quoteByDate);
}

QString CurrencyParser::xmlToString(QByteArray xml)
{
    QTextCodec *codec_1251 = QTextCodec::codecForName("cp-1251");
    return codec_1251->toUnicode(xml);
}
