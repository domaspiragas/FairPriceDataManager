#include "existingcustomer.h"
#include "ui_existingcustomer.h"
#include <QDebug>

ExistingCustomer::ExistingCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExistingCustomer)
{
    ui->setupUi(this);
    //Set main background color
    QPalette pal = palette();
    pal.setColor( QPalette::Window, QColor("#333333"));
    setPalette( pal );
    connect(ui->jobDateBox, SIGNAL(textEdited(QString)), this, SLOT(ForceDateFormat(QString)));
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
    emit ExistingCustomerInfo(ui->customerComboBox->currentText(), ui->carYearBox->text().toUpper(), ui->carMakeBox->text().toUpper(),
                         ui->carModelBox->text().toUpper(), ui->jobWorkBox->text().toUpper(), ui->jobHoursBox->text(), ui->jobPriceBox->text(), ui->jobDateBox->text());
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

void ExistingCustomer::ForceDateFormat(QString textEntered)
{
    // 4 is the size of YYYY before the first /
    if(textEntered.size()<=4)
    {
        //testing if first 4 characters are numbers
        bool ok;
        textEntered.toInt(&ok, 10);
        if(!ok)
        {
            ui->jobDateBox->setText(textEntered.left(textEntered.size()-1));
        }
        // if YYYY are entered and valid
        if(textEntered.size() ==  4 && ok)
        {
            // if 4th number is just added
            if(dateBoxTextLength < textEntered.size())
            {
                ui->jobDateBox->setText(textEntered + "/");
            }
            //if the "/" after YYYY is deleted
            // deletes / and last number of YYYY so we never have YYYY without a "/" after
            else
            {
                ui->jobDateBox->setText(textEntered.left(textEntered.size()-1));
            }
        }
    }
    // Handle the MM part of YYYY/MM/DD
    else if(textEntered.size()>=6 && textEntered.size() <=7)
    {
        // Make sure MM are numbers
        bool ok;
        textEntered.mid(5,textEntered.size()).toInt(&ok, 10);
        if(!ok)
        {
            ui->jobDateBox->setText(textEntered.left(textEntered.size()-1));
        }
        //Handle the "/"
        if(textEntered.size()== 7 && ok)
        {
            // if 7th character is just added
            if(dateBoxTextLength < textEntered.size())
            {
                ui->jobDateBox->setText(textEntered + "/");
            }
            //if the "/" after MM is deleted
            // deletes / and last number of YYYY so we never have YYYY without a "/" after
            else
            {
                ui->jobDateBox->setText(textEntered.left(textEntered.size()-1));
            }
        }
    }
    else if(textEntered.size() >=9 && textEntered.size() <= 10)
    {
        bool ok;
        textEntered.mid(8,textEntered.size()).toInt(&ok, 10);
        if(!ok)
        {
            ui->jobDateBox->setText(textEntered.left(textEntered.size()-1));
        }
    }
    else if(textEntered.size() > 10)
    {
        ui->jobDateBox->setText(textEntered.left(textEntered.size()-1));
    }
    // keep track of current text size in box
    dateBoxTextLength = ui->jobDateBox->text().size();
}
