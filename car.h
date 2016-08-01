#ifndef CAR_H
#define CAR_H
#include <string>

class Car
{
public:
    Car();
    Car(std::string year, std::string make, std::string model);
    std::string GetYear();
    std::string GetMake();
    std::string GetModel();
    void SetYear(std::string year);
    void SetMake(std::string make);
    void SetModel(std::string model);
private:
    std::string m_year;
    std::string m_make;
    std::string m_model;
};

#endif // CAR_H
