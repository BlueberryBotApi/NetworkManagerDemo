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
    //Currency* curr = new Currency();
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
    QString StartDateOfvalue=ui->calendarWidget->selectedDate().toString();//считывем дату
    QString EndDateOfvalue=ui->calendarWidget_2->selectedDate().toString();

    m_manager.get( QNetworkRequest( QUrl(ForOneCheck + StartDateOfvalue+"&date_req2="+EndDateOfvalue+"&VAL_NM_RQ=") ));//делаем запрос
}

void NetworkManagerDemoWidget::onFinished( QNetworkReply* reply ) {
    if( reply->error() == QNetworkReply::NoError ) {
        QString nameOfValue = "";//ui->edUrl->text().trimmed();//считываем валюту, которую необходимо найти
        QString value="";

        QByteArray dataXml = (reply->readAll());/////////////////////////////////////////////////////////////меняем кодировку
        QTextCodec *codec_1251 = QTextCodec::codecForName("cp-1251");

        QString string = codec_1251->toUnicode(dataXml);

        int i = string.indexOf(nameOfValue);// ищем первое вхождение имени валюты
         if(i!=-1)
         {
             i +=nameOfValue.length()+14;//добавляем ее длину и суммарное количество символов в тегах, до значения валюты
             while(string[i]!="<")// пока не встретим конец записи - записывает значение в строку
             {
                 value+=string[i];
                 i++;
             }
         }
         else
         {
              ui->errorString->setText(QString("Данной Валюты нет в списке"));
         }

        ui->textEdit->setText(value);// выводим строку на экран

    } else {
        ui->errorString->setText( reply->errorString() );
    }
   reply->deleteLater();

}

void NetworkManagerDemoWidget::makeComboBox(QMap<QString,QString> map)
{
    ui->comboBox->addItems(ForCodesANDCurrecyNames->codesOfCurrensy.keys());
    ui->bnFind->setEnabled(true);
}
