#include "existingcustomer.h"
#include "ui_existingcustomer.h"

ExistingCustomer::ExistingCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExistingCustomer)
{
    ui->setupUi(this);

}

ExistingCustomer::~ExistingCustomer()
{
    delete ui;
}

void ExistingCustomer::AddCustomerToList(QString name)
{
    ui->customerComboBox->addItem(name);
}

void ExistingCustomer::ReceiveCloseRequest()
{
    ClearClose();
}

void ExistingCustomer::on_submitButton_clicked()
{
    emit ExistingCustomerInfo(ui->customerComboBox->currentText(), ui->carYearBox->text(), ui->carMakeBox->text(),
                         ui->carModelBox->text(), ui->jobWorkBox->text(), ui->jobHoursBox->text(), ui->jobPriceBox->text(), ui->jobDateBox->text());
}

void ExistingCustomer::on_cancelButton_clicked()
{
    ClearClose();
}
void ExistingCustomer::ClearClose()
{
    ui->carMakeBox->setText("");
    ui->carModelBox->setText("");
    ui->carYearBox->setText("");
    ui->jobDateBox->setText("");
    ui->jobHoursBox->setText("");
    ui->jobPriceBox->setText("");
    ui->jobWorkBox->setText("");
    this->hide();;
}
