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

void NewCustomer::ReceiveCloseRequest()
{
    ClearClose();
}

void NewCustomer::on_submitButton_clicked()
{
    emit NewCustomerInfo(ui->customerNameBox->text().toUpper(), ui->customerPhoneNumberBox->text(), ui->carYearBox->text(), ui->carMakeBox->text(),
                         ui->carModelBox->text(), ui->jobWorkBox->text(), ui->jobHoursBox->text(), ui->jobPriceBox->text(), ui->jobDateBox->text());
}

void NewCustomer::on_cancelButton_clicked()
{
    ClearClose();
}
//Clears entry fields and hides the dialog box
void NewCustomer::ClearClose()
{
    ui->carMakeBox->setText("");
    ui->carModelBox->setText("");
    ui->carYearBox->setText("");
    ui->customerNameBox->setText("");
    ui->customerPhoneNumberBox->setText("");
    ui->jobDateBox->setText("");
    ui->jobHoursBox->setText("");
    ui->jobPriceBox->setText("");
    ui->jobWorkBox->setText("");
    this->hide();
}
