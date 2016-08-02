#include "newcustomer.h"
#include "ui_newcustomer.h"
#include <QString>

NewCustomer::NewCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCustomer)
{
    ui->setupUi(this);
}

NewCustomer::~NewCustomer()
{
    delete ui;
}

void NewCustomer::on_submitButton_clicked()
{
    emit NewCustomerInfo(ui->customerNameBox->text(), ui->customerPhoneNumberBox->text(), ui->carYearBox->text(), ui->carMakeBox->text(),
                         ui->carModelBox->text(), ui->jobWorkBox->text(), ui->jobHoursBox->text(), ui->jobPriceBox->text(), ui->jobDateBox->text());
}
