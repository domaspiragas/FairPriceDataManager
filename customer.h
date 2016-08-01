#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<QList>
#include "job.h"


class Customer
{
public:
    Customer(std::string name, std::string phoneNumber);
    std::string GetName();
    std::string GetPhoneNumber();
    void SetName(std::string);
    void SetPhoneNumber(std::string);
    void AddJob(Job* job);
private:
    std::string m_name;
    std::string m_phoneNumber;
    QList<Job> m_jobs;
};

#endif // CUSTOMER_H
