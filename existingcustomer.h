#ifndef EXISTINGCUSTOMER_H
#define EXISTINGCUSTOMER_H

#include <QDialog>

namespace Ui {
class ExistingCustomer;
}

class ExistingCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit ExistingCustomer(QWidget *parent = 0);
    ~ExistingCustomer();

private:
    Ui::ExistingCustomer *ui;

private slots:
    void AddCustomerToList(QString name);

    void on_submitButton_clicked();

signals:
   void ExistingCustomerInfo(QString name, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
};

#endif // EXISTINGCUSTOMER_H
