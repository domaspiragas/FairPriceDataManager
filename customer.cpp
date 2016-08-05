#include "customer.h"

Customer::Customer(QString name, QString phoneNumber)
{
    m_name = name;
    m_phoneNumber = phoneNumber;
}
Customer::~Customer(){}
// Adds a job to the Customer
void Customer::AddJob(Job* job)
{
    m_jobs[job->GetDate()] = job;
}
void Customer::RemoveJob(QString date)
{
    m_jobs.remove(date);
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

QMap<QString, Job *> Customer::GetJobs()
{
    return m_jobs;
}
// Returns the job with the given date
Job* Customer::GetSpecificJob(QString date)
{
    return m_jobs[date];
}
