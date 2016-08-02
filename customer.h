#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<QList>
#include "job.h"


class Customer
{
public:
    Customer(QString name, QString phoneNumber);
    QString GetName();
    QString GetPhoneNumber();
    void SetName(QString);
    void SetPhoneNumber(QString);
    void AddJob(Job* job);
private:
    QString m_name;
    QString m_phoneNumber;
    QList<Job*> m_jobs;
};

#endif // CUSTOMER_H
