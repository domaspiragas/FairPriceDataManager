#include "car.h"

Car::Car(){}
Car::~Car(){}
Car::Car(QString year, QString make, QString model)
{
    m_year = year;
    m_make = make;
    m_model = model;
}

// Getters for Member Variables
QString Car::GetYear() const
{
    return m_year;
}
QString Car::GetMake() const
{
    return m_make;
}
QString Car::GetModel() const
{
    return m_model;
}
// Setters for Member Variables
void Car::SetYear(QString year)
{
    m_year = year;
}
void Car::SetMake(QString make)
{
    m_make = make;
}
void Car::SetModel(QString model)
{
    m_model = model;
}

QDataStream &operator<<(QDataStream &out, const Car &car)
{
    out << car.GetYear() << car.GetMake() << car.GetModel();
    return out;
}
QDataStream &operator>>(QDataStream &in, Car &car)
{
    QString year;
    QString make;
    QString model;
    in >> year >> make >> model;
    car = Car(year, make, model);
    return in;
}
