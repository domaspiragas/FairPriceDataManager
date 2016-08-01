#include "newcustomer.h"
#include "ui_newcustomer.h"

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
