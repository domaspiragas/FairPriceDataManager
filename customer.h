#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<QMap>
#include "job.h"


class Customer
{
public:
    Customer(QString name, QString phoneNumber);
    ~Customer();
    QString GetName();
    QString GetPhoneNumber();
    void SetName(QString);
    void SetPhoneNumber(QString);
    void AddJob(Job* job);
    void RemoveJob(QString);
    QMap<QString, Job*> GetJobs();
    Job* GetSpecificJob(QString date);
private:
    QString m_name;
    QString m_phoneNumber;
    QMap<QString, Job*> m_jobs;
};

#endif // CUSTOMER_H
