#include "job.h"

Job::Job(){}

Job::Job(QString date, Car* car, QString work, QString hours, QString price)
{
    m_date = date;
    m_car = car;
    m_work = work;
    m_hours = hours;
    m_price = price;
}
Job::~Job(){}
// Getters for Member Variables
QString Job::GetDate() const
{
    return m_date;
}
Car* Job::GetCar() const
{
    return m_car;
}
QString Job::GetWork() const
{
    return m_work;
}
QString Job::GetHours() const
{
    return m_hours;
}
QString Job::GetPrice() const
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

QDataStream &operator<<(QDataStream &out, const Job &job)
{
    out << job.GetDate() << *job.GetCar() << job.GetWork() << job.GetHours() << job.GetPrice();
    return out;
}
QDataStream &operator>>(QDataStream &in, Job &job)
{
    QString date;
    Car car;
    QString work;
    QString hours;
    QString price;
    in >> date >> car >> work >> hours >> price;
    job = Job(date, new Car(car.GetYear(), car.GetMake(), car.GetModel()), work, hours, price);
    return in;
}
