#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    m_newCustomerDialog = new NewCustomer();
    m_existingCustomerDialog = new ExistingCustomer();
    // make the cars(main3, jobs1) and work(main4, jobs2) columns longer by default
    ui->mainTable->setColumnWidth(3, 200);
    ui->mainTable->setColumnWidth(4, 250);
    ui->jobsTable->setColumnWidth(1, 200);
    ui->jobsTable->setColumnWidth(2, 250);

    //stretches the last column to the end of the screen
    ui->mainTable->horizontalHeader()->setStretchLastSection(true);
    ui->jobsTable->horizontalHeader()->setStretchLastSection(true);

    HideJobsTableShowMainTable();

    // signal sent when cell is double clicked
    connect(ui->mainTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(HandleDoubleClickedCell(int,int)));
    connect(ui->jobsTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(HandleDoubleClickedCell(int,int)));
    // used to populate drop down
    connect(this, SIGNAL(SendCustomerName(QString)), m_existingCustomerDialog, SLOT(AddCustomerToList(QString)));
    // receive information from dialogs
    connect(m_newCustomerDialog, SIGNAL(NewCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString,QString)), this,
            SLOT(ReceiveNewCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString,QString)));
    connect(m_existingCustomerDialog, SIGNAL(ExistingCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString)), this,
            SLOT(ReceiveExistingCustomerInfo(QString,QString,QString,QString,QString,QString,QString,QString)));
    connect(this, SIGNAL(CloseExistingCustWindow()), m_existingCustomerDialog, SLOT(ReceiveCloseRequest()));
    connect(this, SIGNAL(CloseNewCustWindow()), m_newCustomerDialog, SLOT(ReceiveCloseRequest()));
    connect(ui->actionNew_Customer, SIGNAL(triggered(bool)), this, SLOT(OpenNewCustomerDialog()));
    connect(ui->actionExisting_Customer, SIGNAL(triggered(bool)), this, SLOT(OpenExistingCustomerDialog()));
    connect(ui->backButton, SIGNAL(clicked(bool)), this, SLOT(GoBack()));
    connect(ui->mainTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(SortByDate(int)));


    /*FOR TESTING*/
    m_customers["SOMETHING"] = new Customer("SOMETHING", "911");
    AddJob("SOMETHING", "2016/12/30", new Car("1920","ford","focus"),"struts", "2", "100");
    AddJob("SOMETHING", "2015/08/15", new Car("1980","toyota","focus"),"brakes", "2", "150");

    m_customers["NAME"] = new Customer("NAME", "911-2500-50");
    AddJob("NAME","1995/08/09", new Car("1820","ford","taurus"),"alternator", "2", "150");
    AddJob("NAME","1985/07/12", new Car("1950","toyota","carname"),"brakes", "2", "150");

    m_customers["CUSTOMER"] = new Customer("CUSTOMER", "800-555-5555");
    AddJob("CUSTOMER","2011/02/30", new Car("1855","ford","focus"),"struts", "2", "100");
    AddJob("CUSTOMER","2016/12/31", new Car("1980","toyota","focus"),"brakes", "2", "150");

    m_customers["ZED"] = new Customer("ZED", "911");
    AddJob("ZED","2011/02/30", new Car("1920","ford","focus"),"struts", "2", "100");
    AddJob("ZED", "2005/11/10", new Car("1980","toyota","focus"),"brakes", "2", "150");

    Load();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandleDoubleClickedCell(int row, int col)
{
    //to avoid an additional "connect" statement and slot we check if the main table is showing, if not the jobs table is showing.
    if(ui->mainTable->isVisible())
    {
        // Click on Customer Name
        if(col == 1 )
        {
            OpenJobsView(row, col);
        }
        // Click on Remove
        else if(col == 7)
        {
            m_customers[ui->mainTable->item(row, 1)->text()]->RemoveJob(ui->mainTable->item(row, 0)->text());
           //remove from m_dateCustomerPairs O of N, but best solution for now
            for(int i = 0; i< m_dateCustomerPairs.size(); i++)
            {
                // if the date and name are the same as the row clicked, remove that QPair from list
                if(m_dateCustomerPairs[i].first == ui->mainTable->item(row, 0)->text() && m_dateCustomerPairs[i].second->GetName() == ui->mainTable->item(row, 1)->text())
                {
                    m_dateCustomerPairs.removeAt(i);
                    // end once found and removed
                    break;
                }
            }
            ui->mainTable->removeRow(row);
        }
    }
    // the jobs table is showing
    else if (ui->jobsTable->isVisible())
    {
        // col 5 is the "remove buttons"
        if(col == 5)
        {
            m_customers[ui->nameLabel->text()]->RemoveJob(ui->jobsTable->item(row, 0)->text());
            ui->jobsTable->removeRow(row);
        }
    }
}
void MainWindow::GoBack()
{
    //clear jobs table
    ui->jobsTable->setRowCount(0);
    HideJobsTableShowMainTable();
    Load();
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
    m_customers[name]->AddJob(new Job(date, car, work, hours, price));

    m_dateCustomerPairs.push_back(qMakePair(date, m_customers[name]));

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
    QTableWidgetItem* remove_ = new QTableWidgetItem("X");
    remove_->setFlags(remove_->flags() ^ Qt::ItemIsEditable);

    ui->mainTable->insertRow(ui->mainTable->rowCount());

    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 0, date_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 1, name_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 2, phone_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 3, car_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 4, work_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 5, hours_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 6, price_);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1, 7, remove_);

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
    //top bar
    ui->searchBox->show();
    ui->searchLabel->show();
    ui->addButton->show();
    ui->deleteButton->show();
}
void MainWindow::ShowJobsTableHideMainTable()
{
    ui->mainTable->hide();
    ui->jobsTable->show();
    ui->nameLabel->show();
    ui->phoneNumberLabel->show();
    ui->backButton->show();
    //top bar
    ui->searchBox->hide();
    ui->searchLabel->hide();
    ui->addButton->hide();
    ui->deleteButton->hide();
}

void MainWindow::on_addButton_clicked()
{
    m_newCustomerDialog->show();
}

void MainWindow::on_deleteButton_clicked()
{

}

void MainWindow::OpenJobsView(int row, int col)
{
    //get name - populate jobsTable
    QString name = ui->mainTable->item(row, col)->text();
    ShowJobsTableHideMainTable();

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
        QTableWidgetItem* remove_ = new QTableWidgetItem("X");
        remove_->setFlags(remove_->flags() ^ Qt::ItemIsEditable);

        ui->jobsTable->insertRow(ui->jobsTable->rowCount());

        ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,0,date_);
        ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,1,car_);
        ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,2,work_);
        ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,3,hours_);
        ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,4,price_);
        ui->jobsTable->setItem(ui->jobsTable->rowCount()-1,5,remove_);

    }
    //change labels
    ui->nameLabel->setText(name);
    ui->phoneNumberLabel->setText(m_customers[name]->GetPhoneNumber());
}

void MainWindow::Load()
{
    ui->mainTable->setRowCount(0);
    foreach(Customer* customer, m_customers)
    {
        emit SendCustomerName(customer->GetName());
        foreach(Job* job, customer->GetJobs())
        {
            UpdateListing(customer->GetName(), customer->GetPhoneNumber(), job->GetCar()->GetYear(), job->GetCar()->GetMake(),
                          job->GetCar()->GetModel(), job->GetWork(), job->GetHours(), job->GetPrice(), job->GetDate());
        }
    }
}
void MainWindow::SortByDate(int section)
{
    //if date was clicked
    if(section == 0)
    {
        //sort date/customer pairs by date
        std::sort(m_dateCustomerPairs.begin(), m_dateCustomerPairs.end(), [] (QPair<QString, Customer*>& lhs, QPair<QString, Customer*>& rhs) {
            return lhs.first < rhs.first;
        });
        // clear the table
        ui->mainTable->setRowCount(0);

        //Used to swap from ascending to decending dates
        m_ascendingDateFlag = !m_ascendingDateFlag;
        if(m_ascendingDateFlag)
        {
            for(int i = 0; i < m_dateCustomerPairs.size(); i++)
            {
                Job* job = m_dateCustomerPairs.at(i).second->GetSpecificJob(m_dateCustomerPairs.at(i).first);
                UpdateListing(m_dateCustomerPairs.at(i).second->GetName(), m_dateCustomerPairs.at(i).second->GetPhoneNumber(),job->GetCar()->GetYear(), job->GetCar()->GetMake(),
                              job->GetCar()->GetModel(), job->GetWork(), job->GetHours(), job->GetPrice(), job->GetDate());
            }
        }
        else
        {
            for(int i = m_dateCustomerPairs.size()-1; i >= 0; i--)
            {
                Job* job = m_dateCustomerPairs.at(i).second->GetSpecificJob(m_dateCustomerPairs.at(i).first);
                UpdateListing(m_dateCustomerPairs.at(i).second->GetName(), m_dateCustomerPairs.at(i).second->GetPhoneNumber(),job->GetCar()->GetYear(), job->GetCar()->GetMake(),
                              job->GetCar()->GetModel(), job->GetWork(), job->GetHours(), job->GetPrice(), job->GetDate());
            }
        }
    }
}
