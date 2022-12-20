#include "currencyParser.h"

CurrencyParser::CurrencyParser(QObject* parent)
    : QObject {parent}
{

    this->pNetworkManager = new QNetworkAccessManager();
    connect( this->pNetworkManager, SIGNAL(finished(QNetworkReply*)), SLOT(switchBlock(QNetworkReply*)) );
    connect( this , &CurrencyParser::CodesOfCurrency , &CurrencyParser::onCurrencyRequestFinished);
    connect( this , &CurrencyParser::Quote , &CurrencyParser::onQuoteRequestFinished);

}
CurrencyParser::~CurrencyParser()
{
    delete this->pNetworkManager;
}

void CurrencyParser::switchBlock(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return ;
    }
    QString string = xmlToString(reply->readAll());

    if (string.indexOf("ValCurs")!=-1)
    {
        emit Quote(string);
    }
    else
    {
       emit CodesOfCurrency(string);

    }

    reply->deleteLater();
}




void CurrencyParser::sendCurrencyRequest()
{
    pNetworkManager->get(QNetworkRequest(this->linkCurrency));
}

void CurrencyParser::onCurrencyRequestFinished(const QString &string)
{
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
    emit CurrencyIsReady(currencyCodes);
}

void CurrencyParser::sendQuoteRequest(const QString &startDateOfvalue,const QString &endDateOfvalue,const QString &nameOfCurrency)
{
    this->pNetworkManager->get(QNetworkRequest(QUrl(this->linkQuotePrefix +
                                            "date_req1=" + startDateOfvalue +
                                            "&date_req2=" + endDateOfvalue +
                                            "&VAL_NM_RQ=" + this->currencyCodes[nameOfCurrency])));
}

void CurrencyParser::onQuoteRequestFinished(const QString &string)
{
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
    emit QuoteIsReady(quoteByDate);
}

QString CurrencyParser::xmlToString(QByteArray xml)
{
    QTextCodec *codec_1251 = QTextCodec::codecForName("cp-1251");
    return codec_1251->toUnicode(xml);
}
