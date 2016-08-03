#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

     m_newCustomerDialog = new NewCustomer();
     m_existingCustomerDialog = new ExistingCustomer();

    //stretches the last column to the end of the screen
    ui->mainTable->horizontalHeader()->setStretchLastSection(true);
    ui->jobsTable->horizontalHeader()->setStretchLastSection(true);
    ui->jobsTable->hide();
    ui->nameLabel->hide();
    ui->phoneNumberLabel->hide();
    ui->backButton->hide();

    // signal sent when cell is double clicked
    connect(ui->mainTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(OpenJobsList(int, int)));

    connect(this, SIGNAL(SendCustomerName(QString)), m_existingCustomerDialog, SLOT(AddCustomerToList(QString)));
    connect(m_newCustomerDialog, SIGNAL(NewCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString,QString)), this,
            SLOT(ReceiveNewCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString,QString)));
    connect(m_existingCustomerDialog, SIGNAL(ExistingCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString)), this,
            SLOT(ReceiveExistingCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString)));
    connect(this, SIGNAL(CloseExistingCustWindow()), m_existingCustomerDialog, SLOT(ReceiveCloseRequest()));
    connect(this, SIGNAL(CloseNewCustWindow()), m_newCustomerDialog, SLOT(ReceiveCloseRequest()));
    connect(ui->actionNew_Customer, SIGNAL(triggered(bool)), this, SLOT(OpenNewCustomerDialog()));
    connect(ui->actionExisting_Customer, SIGNAL(triggered(bool)), this, SLOT(OpenExistingCustomerDialog()));
    connect(ui->backButton, SIGNAL(clicked(bool)), this, SLOT(GoBack()));


    //m_newCustomerDialog->show();
    //m_existingCustomerDialog->show();
    //test stuff
    //AddNewRow();
    //NewTable();

    m_customers["SOMETHING"] = new Customer("SOMETHING", "911");
    m_customers["SOMETHING"]->AddJob(new Job("10/20/30", new Car("1920","ford","focus"),"struts", "2", "100"));
    m_customers["SOMETHING"]->AddJob(new Job("11/20/10", new Car("1980","toyota","focus"),"brakes", "2", "150"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenJobsList(int row, int col)
{
    if(col == 1 )
    {
      QString name = ui->mainTable->item(row, col)->text();
      ShowJobsTableHideMainTable();
        //get name - populate jobsTable

        foreach(Job* job, m_customers[name]->GetJobs())
        {

            QTableWidgetItem* date_ = new QTableWidgetItem(job->GetDate());
            date_->setFlags(date_->flags() ^ Qt::ItemIsEditable);
            QTableWidgetItem* car_ = new QTableWidgetItem(job->GetCar()->GetYear() + " " + job->GetCar()->GetMake() + " " + job->GetCar()->GetModel());
            car_->setFlags(car_->flags() ^ Qt::ItemIsEditable);
            QTableWidgetItem* work_ = new QTableWidgetItem(job->GetWork());
            work_->setFlags(work_->flags() ^ Qt::ItemIsEditable);
            QTableWidgetItem* hours_ = new QTableWidgetItem(job->GetHours());
            hours_->setFlags(hours_->flags() ^ Qt::ItemIsEditable);
            QTableWidgetItem* price_ = new QTableWidgetItem(job->GetPrice());
            price_->setFlags(price_->flags() ^ Qt::ItemIsEditable);


            ui->jobsTable->insertRow(ui->jobsTable->rowCount());
            ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,0,date_);
            ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,1,car_);
            ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,2,work_);
            ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,3,hours_);
            ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,4,price_);

        }
        //change labels
        ui->nameLabel->setText(name);
        ui->phoneNumberLabel->setText(m_customers[name]->GetPhoneNumber());


        //ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1, 0, new QLabel(ui->mainTable->item(1,1)->text()));
    }

}
void MainWindow::GoBack()
{
    ui->jobsTable->setRowCount(0);
    HideJobsTableShowMainTable();
}
//Adds customer to the map <name, Customer>
void MainWindow::AddCustomer(QString name, QString phoneNumber)
{
    m_customers[name] = new Customer(name, phoneNumber);
    m_customerNames << name;
    emit SendCustomerName(name);
}

//Adds the given job to the Customer with the given name
void MainWindow::AddJob(QString name, QString date, Car* car, QString work, QString hours, QString price)
{
    /*
     * Emit signal of new car created from given text fields
     */
    m_customers[name]->AddJob(new Job(date, car, work, hours, price));
}
void MainWindow::ReceiveNewCustomerInfo(QString  name, QString  phoneNumber, QString  year, QString  make, QString model,
                     QString work, QString hours, QString price, QString date)
{
    // If the doesn't exist create it
    if(!m_customerNames.contains(name))
    {
        AddCustomer(name, phoneNumber);
    }
    AddJob(name, date, new Car(year, make, model), work, hours, price);
    UpdateListing(name, phoneNumber, year, make, model, work, hours, price, date);
    emit CloseNewCustWindow();
}
void MainWindow::ReceiveExistingCustomerInfo(QString name, QString year, QString make, QString model, QString work, QString hours, QString price, QString date)
{
    AddJob(name, date, new Car(year, make, model), work, hours, price);
    UpdateListing(name, m_customers[name]->GetPhoneNumber(), year, make, model, work, hours, price, date);
    emit CloseExistingCustWindow();
}
void MainWindow::PopulateCustomerDropDown()
{
    //Sort the list to be in alphabetical order
    qSort(m_customerNames);
    foreach(QString name, m_customerNames)
    {
        emit SendCustomerName(name.toUpper());
    }
}
void MainWindow::UpdateListing(QString name, QString phoneNumber, QString year, QString make, QString model, QString work, QString hours, QString price, QString date)
{
    QTableWidgetItem* date_ = new QTableWidgetItem(date);
    date_->setFlags(date_->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem* name_ = new QTableWidgetItem(name);
    name_->setFlags(name_->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem* phone_ = new QTableWidgetItem(phoneNumber);
    phone_->setFlags(phone_->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem* car_ = new QTableWidgetItem(year + " " + make + " " + model);
    car_->setFlags(car_->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem* work_ = new QTableWidgetItem(work);
    work_->setFlags(work_->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem* hours_ = new QTableWidgetItem(hours);
    hours_->setFlags(hours_->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem* price_ = new QTableWidgetItem(price);
    price_->setFlags(price_->flags() ^ Qt::ItemIsEditable);


    ui->mainTable->insertRow(ui->mainTable->rowCount());
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 0, date_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 1, name_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 2, phone_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 3, car_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 4, work_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 5, hours_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 6, price_);

}
void MainWindow::OpenNewCustomerDialog()
{
    m_newCustomerDialog->show();
}
void MainWindow::OpenExistingCustomerDialog()
{
    m_existingCustomerDialog->show();
}

void MainWindow::HideJobsTableShowMainTable()
{
    ui->mainTable->show();
    ui->jobsTable->hide();
    ui->nameLabel->hide();
    ui->phoneNumberLabel->hide();
    ui->backButton->hide();
}
void MainWindow::ShowJobsTableHideMainTable()
{
    ui->mainTable->hide();

    ui->jobsTable->show();
    ui->nameLabel->show();
    ui->phoneNumberLabel->show();
    ui->backButton->show();
}
