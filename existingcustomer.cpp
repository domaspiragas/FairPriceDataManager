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
