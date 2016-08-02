#ifndef NEWCUSTOMER_H
#define NEWCUSTOMER_H

#include <QDialog>

namespace Ui {
class NewCustomer;
}

class NewCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit NewCustomer(QWidget *parent = 0);
    ~NewCustomer();

private slots:
    void on_submitButton_clicked();

private:
    Ui::NewCustomer *ui;

signals:
    void NewCustomerInfo(QString name, QString phoneNumber, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);
};

#endif // NEWCUSTOMER_H