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
QString Car::GetYear()
{
    return m_year;
}
QString Car::GetMake()
{
    return m_make;
}
QString Car::GetModel()
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
