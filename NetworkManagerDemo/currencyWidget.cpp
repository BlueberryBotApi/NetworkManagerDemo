#include "currencyWidget.h"
#include "ui_currencyWidget.h"


#include <QNetworkReply>

CurrencyWidget::CurrencyWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CurrencyWidget) {

    ui->setupUi(this);
    ui->bnFind->setEnabled(false);
    ui->calendarWidget->setMaximumDate(QDate::currentDate());
    ui->calendarWidget_2->setMaximumDate(QDate::currentDate());

    this->quoteByDate = QMap<QString,QString>();

    this->pCurrencyParser = new CurrencyParser();
    pCurrencyParser->sendCurrencyRequest();
    connect( pCurrencyParser, &CurrencyParser::CurrencyIsReady, this, &CurrencyWidget::onCurrencyMapIsReady);

    connect(ui->bnFind, SIGNAL(clicked(bool)), SLOT(onGo()) );
    connect(pCurrencyParser, &CurrencyParser::QuoteIsReady, this, &CurrencyWidget::onQuoteMapIsReady);
}

CurrencyWidget::~CurrencyWidget() {
    delete ui;
    delete this->pCurrencyParser;
}

void CurrencyWidget::onCurrencyMapIsReady(QMap<QString,QString> map)
{
    this->currencyCodes = map;

    this->makeComboBox();
}

void CurrencyWidget::onGo() {
    ui->bnFind->setEnabled(false);
    ui->tableWidget->clearContents();
    ui->errorString->clear();

    QString StartDateOfvalue = ui->calendarWidget->selectedDate().toString("dd/MM/yyyy");
    QString EndDateOfvalue = ui->calendarWidget_2->selectedDate().toString("dd/MM/yyyy");
    QString nameOfCurrency = ui->comboBox->currentText();

    this->pCurrencyParser->sendQuoteRequest(StartDateOfvalue, EndDateOfvalue, nameOfCurrency);
}

void CurrencyWidget::onQuoteMapIsReady(QMap<QString,QString> map) {
    this->quoteByDate = map;
    this->pCurrencyParser->quoteByDate = QMap<QString,QString>();

    this->makeTable();
}

void CurrencyWidget::makeComboBox()
{
    ui->comboBox->addItems(this->currencyCodes.keys());
    ui->bnFind->setEnabled(true);
}

void CurrencyWidget::makeTable()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    if(this->quoteByDate.isEmpty())
    {
        ui->errorString->setText("Значения данной валюты отсутсвуют в выбранном временном промежутке");
    }
    QMap<QString, QString>::const_iterator i;
    for (i = this->quoteByDate.constBegin(); i != this->quoteByDate.constEnd(); i++) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

        QTableWidgetItem* newItem = new QTableWidgetItem();
        newItem->setText(i.key());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);

        newItem = new QTableWidgetItem();
        newItem->setText(i.value());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newItem);
    }

    ui->bnFind->setEnabled(true);
}
