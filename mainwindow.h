#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QMap>
#include <QSet>
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
    //Store Customer Names to populate Drop Down
    QList<QString> m_customerNames;
    QTableWidget* newTable;
    QPushButton* backButton;

    NewCustomer* m_newCustomerDialog;
    ExistingCustomer* m_existingCustomerDialog;
    void HideJobsTableShowMainTable();
    void ShowJobsTableHideMainTable();
    void PopulateCustomerDropDown();
    void UpdateListing(QString name, QString phoneNumber, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);


private slots:
    void GoBack();
    void OpenJobsList(int, int);
    void AddCustomer(QString name, QString phoneNumber);
    void AddJob(QString name, QString date, Car* car, QString work, QString hours, QString price);
    void ReceiveNewCustomerInfo(QString name, QString phoneNumber, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
    void ReceiveExistingCustomerInfo(QString name, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
    void OpenNewCustomerDialog();
    void OpenExistingCustomerDialog();


signals:
    void SendCustomerName(QString name);
    void CloseNewCustWindow();
    void CloseExistingCustWindow();
};

#endif // MAINWINDOW_H
