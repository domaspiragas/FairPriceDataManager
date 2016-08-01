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
    //stretches the last column to the end of the screen
    ui->mainTable->horizontalHeader()->setStretchLastSection(true);
    // signal sent when cell is double clicked
    connect(ui->mainTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(NewTable(int, int)));


    m_newCustomerDialog = new NewCustomer();
    m_newCustomerDialog->show();

    m_existingCustomerDialog = new ExistingCustomer();
    m_existingCustomerDialog->show();
    //test stuff
    AddNewRow();
    //NewTable();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddNewRow()
{
     QLabel* date = new QLabel(" 10/10/10");
     QLabel* name = new QLabel(" John Smith");
     QLabel* phone = new QLabel(" 801-811-1118");
     QLabel* car = new QLabel(" 2010 Subaru Forester");
     QLabel* work = new QLabel(" Alternator, Window Motor");
     QLabel* hours = new QLabel(" 5.2");
     QLabel* price = new QLabel(" 280.55");
     ui->mainTable->insertRow(ui->mainTable->rowCount());
     ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,0,date);
     ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,1,name);
     ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,2,phone);
     ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,3,car);
     ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,4,work);
     ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,5,hours);
     ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1,6,price);
     ui->mainTable->setCellWidget(ui->mainTable->rowCount()-1, 0, new QLabel(ui->mainTable->item(1,1)->text()));
}
void MainWindow::NewTable(int row, int col)
{
    if(col == 1 )
    {
    newTable = new QTableWidget;
    newTable->setColumnCount(5);
    newTable->setRowCount(5);
    QStringList labels;
    labels<<"date"<<"name"<<"phone"<<"car"<<"test";
    newTable->setHorizontalHeaderLabels(labels);
    ui->mainTable->setVisible(false);
    newTable->horizontalHeader()->setStretchLastSection(true);
    ui->verticalLayout->addWidget(newTable);
    backButton = new QPushButton("back");
    backButton->setMaximumWidth(50);
    connect(backButton, SIGNAL(clicked(bool)), this, SLOT(GoBack()));
    ui->verticalLayout->addWidget(backButton);
    }
}
void MainWindow::GoBack()
{
    newTable->clear();
    newTable->setVisible(false);
    backButton->hide();
    ui->mainTable->show();

}
//Adds customer to the map <name, Customer>
void MainWindow::AddCustomer(std::string name, std::string phoneNumber)
{
    m_customers[name] = new Customer(name, phoneNumber);
}

//Adds the given job to the Customer with the given name
void MainWindow::AddJob(std::string name, std::string date, Car car, std::string work, std::string hours, std::string price)
{
    /*
     * Emit signal of new car created from given text fields
     */
    m_customers[name]->AddJob(new Job(date, car, work, hours, price));
}
