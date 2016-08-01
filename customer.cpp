#include "customer.h"

Customer::Customer(std::string name, std::string phoneNumber)
{
    m_name = name;
    m_phoneNumber = phoneNumber;
}
// Adds a job to the Customer
void Customer::AddJob(Job* job)
{
    m_jobs.push_back(*job);
}
//Getters for Member Variables
std::string Customer::GetName()
{
    return m_name;
}
std::string Customer::GetPhoneNumber()
{
    return m_phoneNumber;
}
//Setters for Member Variables
void Customer::SetName(std::string name)
{
    m_name = name;
}
void Customer::SetPhoneNumber(std::string phoneNumber)
{
    m_phoneNumber = phoneNumber;
}

