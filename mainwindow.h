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
    QList<QPair<QString, Customer*>> m_dateCustomerPairs;
    QList<QPair<QString, Customer*>> m_searchDateCustomerPairs;
    NewCustomer* m_newCustomerDialog;
    ExistingCustomer* m_existingCustomerDialog;
    bool m_ascendingDateFlag;
    bool m_searchBeingUsed;
    void HideJobsTableShowMainTable();
    void ShowJobsTableHideMainTable();
    void UpdateListing(QString name, QString phoneNumber, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
    void OpenJobsView(int row, int col);
    void Load();


private slots:
    void GoBack();
    void HandleDoubleClickedCell(int, int);
    void AddCustomer(QString name, QString phoneNumber);
    void AddJob(QString name, QString date, Car* car, QString work, QString hours, QString price);
    void ReceiveNewCustomerInfo(QString name, QString phoneNumber, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
    void ReceiveExistingCustomerInfo(QString name, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
    void OpenNewCustomerDialog();
    void OpenExistingCustomerDialog();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void SortByDate(int);
    void SearchSort(QString);

signals:
    void SendCustomerName(QString name);
    void CloseNewCustWindow();
    void CloseExistingCustWindow();
};

#endif // MAINWINDOW_H
