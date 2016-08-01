#include "job.h"

Job::Job(std::string date, Car car, std::string work, std::string hours, std::string price)
{
    m_date = date;
    m_car = car;
    m_work = work;
    m_hours = hours;
    m_price = price;
}

// Getters for Member Variables
std::string Job::GetDate()
{
    return m_date;
}
Car Job::GetCar()
{
    return m_car;
}
std::string Job::GetWork()
{
    return m_work;
}
std::string Job::GetHours()
{
    return m_hours;
}
std::string Job::GetPrice()
{
    return m_price;
}
// Setters for Member Variables
void Job::SetDate(std::string date)
{
    m_date = date;
}
void Job::SetCar(Car car)
{
    m_car = car;
}
void Job::SetWork(std::string work)
{
    m_work = work;
}
void Job::SetHours(std::string hours)
{
    m_hours = hours;
}
void Job::SetPrice(std::string price)
{
    m_price = price;
}
