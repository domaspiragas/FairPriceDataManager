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
};

#endif // EXISTINGCUSTOMER_H
