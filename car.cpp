#include "car.h"

Car::Car(){}
Car::Car(std::string year, std::string make, std::string model)
{
    m_year = year;
    m_make = make;
    m_model = model;
}

// Getters for Member Variables
std::string Car::GetYear()
{
    return m_year;
}
std::string Car::GetMake()
{
    return m_make;
}
std::string Car::GetModel()
{
    return m_model;
}
// Setters for Member Variables
void Car::SetYear(std::string year)
{
    m_year = year;
}
void Car::SetMake(std::string make)
{
    m_make = make;
}
void Car::SetModel(std::string model)
{
    m_model = model;
}
