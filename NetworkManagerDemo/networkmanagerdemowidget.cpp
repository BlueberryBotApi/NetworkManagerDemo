#include "networkmanagerdemowidget.h"
#include "ui_networkmanagerdemowidget.h"


#include <QNetworkReply>

NetworkManagerDemoWidget::NetworkManagerDemoWidget( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::NetworkManagerDemoWidget ) {
    ui->setupUi( this );
    ui->bnFind->setEnabled(false);
    ui->calendarWidget->setMaximumDate(QDate::currentDate());
    ui->calendarWidget_2->setMaximumDate(QDate::currentDate());

    this->dateAndCurrencyNamesForTable =  QMap <QString,QString>();
    this->ForCodesANDCurrecyNames = new Currency();
    ForCodesANDCurrecyNames->takeXSDScheme();

    connect(ForCodesANDCurrecyNames,&Currency::QMapIsReady,this,&NetworkManagerDemoWidget::makeComboBox);
    connect( ui->bnFind, SIGNAL( clicked(bool) ), SLOT( onGo() ) );
    connect( &m_manager, SIGNAL( finished(QNetworkReply*) ), SLOT( onFinished(QNetworkReply*) ) );
}

NetworkManagerDemoWidget::~NetworkManagerDemoWidget() {
    delete this->ForCodesANDCurrecyNames;
    delete ui;
}

void NetworkManagerDemoWidget::onGo() {
    //ui->lbStatus->setText( "Working..." );
    ui->bnFind->setEnabled(false);
    QString StartDateOfvalue=ui->calendarWidget->selectedDate().toString("dd/MM/yyyy");//считывем дату указывая формат
    QString EndDateOfvalue=ui->calendarWidget_2->selectedDate().toString("dd/MM/yyyy");
    QString nameOfCurrency = ui->comboBox->currentText();
    m_manager.get( QNetworkRequest( QUrl(ForOneCheck + StartDateOfvalue+"&date_req2="+EndDateOfvalue+"&VAL_NM_RQ="+ForCodesANDCurrecyNames->codesOfCurrensy[nameOfCurrency]) ));//делаем запрос
}

void NetworkManagerDemoWidget::onFinished( QNetworkReply* reply ) {
    if( reply->error() == QNetworkReply::NoError ) {
        QByteArray dataXml = (reply->readAll());/////////////////////////////////////////////////////////////меняем кодировку
        QTextCodec *codec_1251 = QTextCodec::codecForName("cp-1251");
        QString string = codec_1251->toUnicode(dataXml);
//////////////////////////////////////////////////////////////////////////////////////////////////////парсим
        QString buf,date;
            int i=0,j=0;
        while(i!=-1)
        {
            buf="";
            i = string.indexOf("Record Date",j);
            if(i!=-1)
            {
                i+=13;
                while(string[i]!='"')
                {
                    buf+=string[i];
                    i++;
                }
                j=i;
                date = buf;
                buf="";
                i = string.indexOf("Value",j);
                i+=6;
                while(string[i]!='<')
                {
                    buf+=string[i];
                    i++;
                }
                this->dateAndCurrencyNamesForTable[date]=buf;
                j=i;
            }
//////////////////////////////////////////////////////////////////////////////////////////////////////
        }
    } else {
        ui->errorString->setText( reply->errorString() );
    }
    reply->deleteLater();
    this->makeTable(dateAndCurrencyNamesForTable);
}

void NetworkManagerDemoWidget::makeComboBox(QMap<QString,QString> map)
{
    ui->comboBox->addItems(ForCodesANDCurrecyNames->codesOfCurrensy.keys());
    ui->bnFind->setEnabled(true);
}
void NetworkManagerDemoWidget::makeTable(QMap<QString,QString> map)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

        QMap<QString, QString>::const_iterator i = map.constBegin();
        while (i != map.constEnd()) {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setText(i.key());
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);
            newItem = new QTableWidgetItem();
            newItem->setText(i.value());
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newItem);
            ++i;
        }
    ui->bnFind->setEnabled(true);
}
