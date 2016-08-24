#include "customer.h"

Customer::Customer(){}
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
QString Customer::GetName() const
{
    return m_name;
}
QString Customer::GetPhoneNumber() const
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

QMap<QString, Job *> Customer::GetJobs() const
{
    return m_jobs;
}
// Returns the job with the given date
Job* Customer::GetSpecificJob(QString date) const
{
    return m_jobs[date];
}

QDataStream &operator<<(QDataStream &out, const Customer &customer)
{
    // can't serialize pointers, store into map w/ no pointers
    QMap<QString, Job> jobs;
    foreach(Job* job, customer.GetJobs())
    {
        jobs[job->GetDate()] = *job;
    }
    out << customer.GetName() << customer.GetPhoneNumber() << jobs;
    return out;
}
QDataStream &operator>>(QDataStream &in, Customer &customer)
{
    QString name;
    QString phoneNumber;
    QMap<QString, Job> jobsNoPointer;

    in >> name >> phoneNumber >> jobsNoPointer;
    customer = Customer(name, phoneNumber);
    foreach(Job job, jobsNoPointer)
    {
        customer.AddJob(new Job(job.GetDate(), job.GetCar(), job.GetWork(), job.GetHours(), job.GetPrice()));
    }
    return in;
}
