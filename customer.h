#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<QMap>
#include "job.h"


class Customer
{
public:
    Customer();
    Customer(QString name, QString phoneNumber);
    ~Customer();
    QString GetName() const;
    QString GetPhoneNumber() const;
    void SetName(QString);
    void SetPhoneNumber(QString);
    void AddJob(Job* job);
    void RemoveJob(QString);
    QMap<QString, Job*> GetJobs() const;
    Job* GetSpecificJob(QString date) const;
private:
    QString m_name;
    QString m_phoneNumber;
    QMap<QString, Job*> m_jobs;
};
QDataStream &operator<<(QDataStream &out, const Customer &customer);
QDataStream &operator>>(QDataStream &in, Customer &customer);

#endif // CUSTOMER_H
