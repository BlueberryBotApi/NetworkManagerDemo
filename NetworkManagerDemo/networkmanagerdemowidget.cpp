#include "networkmanagerdemowidget.h"
#include "ui_networkmanagerdemowidget.h"


#include <QNetworkReply>

NetworkManagerDemoWidget::NetworkManagerDemoWidget( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::NetworkManagerDemoWidget ) {
    ui->setupUi( this );

    connect( ui->bnFind, SIGNAL( clicked(bool) ), SLOT( onGo() ) );
    connect( &m_manager, SIGNAL( finished(QNetworkReply*) ), SLOT( onFinished(QNetworkReply*) ) );
}

NetworkManagerDemoWidget::~NetworkManagerDemoWidget() {
    delete ui;
}

void NetworkManagerDemoWidget::onGo() {
    //ui->lbStatus->setText( "Working..." );
    QString dataOfvalue=ui->dataOfsearch->text().trimmed();//считывем дату


    QDate setTime = QDate::fromString (dataOfvalue,"dd.MM.yyyy");
    QDate datat= QDate::currentDate();
    if(setTime > QDate::currentDate())
    {
        ui->errorString->setText(QString("Введите приемлимую дату"));
    }

   // ForOneCheck+=dataOfvalue;// добавляем ее к url
    m_manager.get( QNetworkRequest( QUrl(ForOneCheck + dataOfvalue) ));//делаем запрос
}

void NetworkManagerDemoWidget::onFinished( QNetworkReply* reply ) {
    if( reply->error() == QNetworkReply::NoError ) {
        QString nameOfValue = ui->edUrl->text().trimmed();//считываем валюту, которую необходимо найти
        QString value="";

        QByteArray dataXml = (reply->readAll());/////////////////////////////////////////////////////////////меняем кодировку
         QByteArray dataXml1;
        QTextCodec *codec_1251 = QTextCodec::codecForName("cp-1251");

        QString string = codec_1251->toUnicode(dataXml);
        QTextCodec *codec_utf8 = QTextCodec::codecForName("UTF-8");

        dataXml=codec_utf8->fromUnicode(string);/////////////////////////////////////////////////////////////

        int i = string.indexOf(nameOfValue);// ищем первое вхождение имени валюты
         if(i!=-1)
         {
             i +=nameOfValue.length()+14;//добавляем ее длинну и суммарное количество символов в тегах, до значения валюты
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

//        QXmlStreamReader xmlDoc(dataXml);
//        while (!xmlDoc.atEnd() && !xmlDoc.hasError()) {
//            //data+=xmlDoc.readElementText();
//             // QXmlStreamReader::TokenType token = xmlDoc.readNext();
//           xmlDoc.readNext();

//           if(xmlDoc.isStartElement())
//           {
//                xmlDoc.readNext();
//                qDebug()<< xmlDoc.text();
//           }
//           else
//           {
//               qDebug()<< xmlDoc.name();
//           }//&& xmlDoc.name()== QString("Name")
////           if(xmlDoc.name()=="Name" && xmlDoc.readElementText()==nameOfValue)
////           {
////               xmlDoc.readNextStartElement();
////               if(xmlDoc.isStartElement() && xmlDoc.name()=="Value")
////               {
////                 //  valRate = xmlDoc.readElementText().toDouble();
////                   value=xmlDoc.readElementText();
////          break;
////               }
////           }
//          if (xmlDoc.hasError())
//          {
//              ui->lbStatus->setText( xmlDoc.errorString() );
//              qDebug() << (xmlDoc.errorString()) ;
//          }
//        }
        ui->textEdit->setText(value);// выводим строку на экран

    } else {
        ui->errorString->setText( reply->errorString() );
    }
   reply->deleteLater();

}
