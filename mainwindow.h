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
    QMap<QString, Customer*> m_customers;
    void AddNewRow();
    QTableWidget* newTable;
    QPushButton* backButton;

    NewCustomer* m_newCustomerDialog;
    ExistingCustomer* m_existingCustomerDialog;



private slots:
    void GoBack();
    void NewTable(int, int);
    void AddCustomer(QString name, QString phoneNumber);
    void AddJob(QString name, QString date, Car* car, QString work, QString hours, QString price);
    void ReceiveNewCustomerInfo(QString name, QString phoneNumber, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
};

#endif // MAINWINDOW_H
