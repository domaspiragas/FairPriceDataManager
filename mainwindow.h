#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QMap>
#include "customer.h"
#include "newcustomer.h"
#include "existingcustomer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //Main storage of Data
    QMap<std::string, Customer*> m_customers;
    void AddNewRow();
    QTableWidget* newTable;
    QPushButton* backButton;

    NewCustomer* m_newCustomerDialog;
    ExistingCustomer* m_existingCustomerDialog;



private slots:
    void GoBack();
    void NewTable(int, int);
    void AddCustomer(std::string name, std::string phoneNumber);
    void AddJob(std::string name, std::string date, Car car, std::string work, std::string hours, std::string price);
};

#endif // MAINWINDOW_H
