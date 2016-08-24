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
    void ReceiveCloseRequest();
    void ForceDateFormat(QString textEntered);
    void ForcePhoneNumberFormat(QString textEntered);
    void on_submitButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::NewCustomer *ui;
    int m_dateBoxTextLength;
    int m_phoneNumberBoxTextLength;
    void ClearClose();

signals:
    void NewCustomerInfo(QString name, QString phoneNumber, QString year, QString make, QString model, QString work, QString hours, QString price, QString date);

};

#endif // NEWCUSTOMER_H
