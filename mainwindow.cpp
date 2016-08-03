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
    // signal sent when cell is double clicked
    connect(ui->mainTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(NewTable(int, int)));
    connect(this, SIGNAL(SendCustomerName(QString)), m_existingCustomerDialog, SLOT(AddCustomerToList(QString)));
    connect(m_newCustomerDialog, SIGNAL(NewCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString,QString)), this,
            SLOT(ReceiveNewCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString,QString)));
    connect(m_existingCustomerDialog, SIGNAL(ExistingCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString)), this,
            SLOT(ReceiveExistingCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString)));
    connect(this, SIGNAL(CloseExistingCustWindow()), m_existingCustomerDialog, SLOT(ReceiveCloseRequest()));
        connect(this, SIGNAL(CloseNewCustWindow()), m_newCustomerDialog, SLOT(ReceiveCloseRequest()));
    connect(ui->actionNew_Customer, SIGNAL(triggered(bool)), this, SLOT(OpenNewCustomerDialog()));
    connect(ui->actionExisting_Customer, SIGNAL(triggered(bool)), this, SLOT(OpenExistingCustomerDialog()));


    //m_newCustomerDialog->show();
    //m_existingCustomerDialog->show();
    //test stuff
    //AddNewRow();
    //NewTable();
    m_customerNames << "dog" << "this" << "is" << "more" << "names" << "and" << "something" << "words" << "And";
    m_customers["SOMETHING"] = new Customer("SOMETHING", "911");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NewTable(int row, int col)
{
//    if(col == 1 )
//    {
//    newTable = new QTableWidget;
//    newTable->setColumnCount(5);
//    newTable->setRowCount(5);
//    QStringList labels;
//    labels<<"date"<<"name"<<"phone"<<"car"<<"test";
//    newTable->setHorizontalHeaderLabels(labels);
//    ui->mainTable->setVisible(false);
//    newTable->horizontalHeader()->setStretchLastSection(true);
//    ui->verticalLayout->addWidget(newTable);
//    backButton = new QPushButton("back");
//    backButton->setMaximumWidth(50);
//    connect(backButton, SIGNAL(clicked(bool)), this, SLOT(GoBack()));
//    ui->verticalLayout->addWidget(backButton);
//    }
    PopulateCustomerDropDown();
}
void MainWindow::GoBack()
{
    newTable->clear();
    newTable->setVisible(false);
    backButton->hide();
    ui->mainTable->show();

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

    QLabel* date_ = new QLabel(" " + date);
    QLabel* name_ = new QLabel(" " + name);
    QLabel* phone_ = new QLabel(" " + phoneNumber);
    QLabel* car_ = new QLabel(" " + year + " " + make + " " + model);
    QLabel* work_ = new QLabel(" " + work);
    QLabel* hours_ = new QLabel(" " + hours);
    QLabel* price_ = new QLabel(" " + price);
    ui->mainTable->insertRow(ui->mainTable->rowCount());
    ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,0,date_);
    ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,1,name_);
    ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,2,phone_);
    ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,3,car_);
    ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,4,work_);
    ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,5,hours_);
    ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,6,price_);

   // m_newCustomerDialog->hide();

    //ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1, 0, new QLabel(ui->mainTable->item(1,1)->text()));
}
void MainWindow::OpenNewCustomerDialog()
{
    m_newCustomerDialog->show();
}
void MainWindow::OpenExistingCustomerDialog()
{
    m_existingCustomerDialog->show();
}
