#include "newcustomer.h"
#include "ui_newcustomer.h"
#include <QString>

NewCustomer::NewCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCustomer)
{
    ui->setupUi(this);
    //Set main background color
    QPalette pal = palette();
    pal.setColor( QPalette::Window, QColor("#333333"));
    setPalette( pal );
    //set icon
    this->setWindowIcon(QIcon(":/logo/Images/CarIcon.png"));
    // Connect Slots and Signals
    connect(ui->jobDateBox, SIGNAL(textEdited(QString)), this, SLOT(ForceDateFormat(QString)));
    connect(ui->customerPhoneNumberBox, SIGNAL(textEdited(QString)), this, SLOT(ForcePhoneNumberFormat(QString)));
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
    emit NewCustomerInfo(ui->customerNameBox->text().toUpper(), ui->customerPhoneNumberBox->text(), ui->carYearBox->text().toUpper(), ui->carMakeBox->text().toUpper(),
                         ui->carModelBox->text().toUpper(), ui->jobWorkBox->text().toUpper(), ui->jobHoursBox->text(), ui->jobPriceBox->text(), ui->jobDateBox->text());
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
/*
    Handles The formating for the date box
*/
void NewCustomer::ForceDateFormat(QString textEntered)
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
            if(m_dateBoxTextLength < textEntered.size())
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
            if(m_dateBoxTextLength < textEntered.size())
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
    m_dateBoxTextLength = ui->jobDateBox->text().size();
}
void NewCustomer::ForcePhoneNumberFormat(QString textEntered)
{
    if(textEntered.size() <= 3)
    {
        //testing if first 3 characters are numbers
        bool ok;
        textEntered.toInt(&ok, 10);
        if(!ok)
        {
            ui->customerPhoneNumberBox->setText(textEntered.left(textEntered.size()-1));
        }
        // if YYYY are entered and valid
        if(textEntered.size() ==  3 && ok)
        {
            // if 3rd number is just added
            if(m_phoneNumberBoxTextLength < textEntered.size())
            {
                ui->customerPhoneNumberBox->setText(textEntered + "-");
            }
            //if the "-"
            // deletes "-" and last number so we never have the area code without a "-" after
            else
            {
                ui->customerPhoneNumberBox->setText(textEntered.left(textEntered.size()-1));
            }
        }

    }
    else if(textEntered.size() >= 5 && textEntered.size()<=7)
    {
        bool ok;
        textEntered.mid(4,textEntered.size()).toInt(&ok, 10);
        if(!ok)
        {
            ui->customerPhoneNumberBox->setText(textEntered.left(textEntered.size()-1));
        }
        //Handle the "-"
        if(textEntered.size()== 7 && ok)
        {
            // if 7th character is just added add "-"
            if(m_phoneNumberBoxTextLength < textEntered.size())
            {
                ui->customerPhoneNumberBox->setText(textEntered + "-");
            }
            //if the second "-" is deleted remove the last number as well
            else
            {
                ui->customerPhoneNumberBox->setText(textEntered.left(textEntered.size()-1));
            }
        }
    }
    // Limit the size to 12
    else if(textEntered.size() > 12)
    {
        ui->customerPhoneNumberBox->setText(textEntered.left(textEntered.size()-1));
    }
    m_phoneNumberBoxTextLength = ui->customerPhoneNumberBox->text().size();
}
