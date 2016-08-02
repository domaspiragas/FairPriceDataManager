#include "customer.h"

Customer::Customer(QString name, QString phoneNumber)
{
    m_name = name;
    m_phoneNumber = phoneNumber;
}
// Adds a job to the Customer
void Customer::AddJob(Job* job)
{
    m_jobs.push_back(job);
}
//Getters for Member Variables
QString Customer::GetName()
{
    return m_name;
}
QString Customer::GetPhoneNumber()
{
    return m_phoneNumber;
}
//Setters for Member Variables
void Customer::SetName(QString name)
{
    m_name = name;
}
void Customer::SetPhoneNumber(QString phoneNumber)
{
    m_phoneNumber = phoneNumber;
}

