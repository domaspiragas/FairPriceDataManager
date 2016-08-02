#include "job.h"

Job::Job(QString date, Car* car, QString work, QString hours, QString price)
{
    m_date = date;
    m_car = car;
    m_work = work;
    m_hours = hours;
    m_price = price;
}

// Getters for Member Variables
QString Job::GetDate()
{
    return m_date;
}
Car* Job::GetCar()
{
    return m_car;
}
QString Job::GetWork()
{
    return m_work;
}
QString Job::GetHours()
{
    return m_hours;
}
QString Job::GetPrice()
{
    return m_price;
}
// Setters for Member Variables
void Job::SetDate(QString date)
{
    m_date = date;
}
void Job::SetCar(Car* car)
{
    m_car = car;
}
void Job::SetWork(QString work)
{
    m_work = work;
}
void Job::SetHours(QString hours)
{
    m_hours = hours;
}
void Job::SetPrice(QString price)
{
    m_price = price;
}
