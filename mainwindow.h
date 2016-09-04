#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QMap>
#include <QSet>
#include <QStack>
#include "customer.h"
#include "newcustomer.h"
#include "existingcustomer.h"
#include <QCloseEvent>
#include <QVector>

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
    //Temporary storage for Customer Name - Phone Numbers
    QMap<QString, QString> m_tempCustomerInfo;
    //Store Customer Names to populate Drop Down
    QList<QString> m_customerNames;
    QList<QPair<QString, Customer*>> m_dateCustomerPairs;
    QList<QPair<QString, Customer*>> m_searchDateCustomerPairs;
    //Stores save file names, initialized to size 10
    QList<QString> m_saveFileNames = QList<QString>{"","","","","","","","","","",};
    int m_lastSavedIndex;
    //List for storing potentially empty customers
    QList<QString> m_emptyCustomers;
    //Undo And Redo Stacks, QPair<QPair<CustomerName, Job>, bool(removed == true, added == false)>
    QStack<QPair<QPair<QString, Job*>, bool>> undoStack;
    QStack<QPair<QPair<QString, Job*>, bool>> redoStack;
    NewCustomer* m_newCustomerDialog;
    ExistingCustomer* m_existingCustomerDialog;
    bool m_ascendingDateFlag;
    bool m_jobDescendingDateFlag;
    bool m_alphabeticalNameFlag;
    bool m_searchBeingUsed;
    bool m_unsavedChanges;
    void HideJobsTableShowMainTable();
    void ShowJobsTableHideMainTable();
    void UpdateListing(QString name, QString phoneNumber, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
    void OpenJobsView(int row, int col);
    void Load();

protected:
     void closeEvent(QCloseEvent *event);

private slots:
    void GoBack();
    void HandleDoubleClickedCell(int, int);
    void AddCustomer(QString name, QString phoneNumber);
    void AddJob(QString name, QString date, Car* car, QString work, QString hours, QString price);
    void ReceiveNewCustomerInfo(QString name, QString phoneNumber, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
    void ReceiveExistingCustomerInfo(QString name, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
    void OpenNewCustomerDialog();
    void OpenExistingCustomerDialog();
    void SortByDate(int);
    void SortByName(int);
    void SortJobsTableByDate(int);
    void SortSearched(QString);
    void HandleUndo();
    void HandleRedo();
    void Save();
    void LoadFromFile();
    void LoadBackupSave();


signals:
    void SendCustomerName(QString name);
    void CloseNewCustWindow();
    void CloseExistingCustWindow();

};

#endif // MAINWINDOW_H
