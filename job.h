#ifndef JOB_H
#define JOB_H
#include "car.h"

class Job
{
public:
    Job(std::string date, Car car, std::string work, std::string hours, std::string price);
    std::string GetDate();
    Car GetCar();
    std::string GetWork();
    std::string GetHours();
    std::string GetPrice();
    void SetDate(std::string date);
    void SetCar(Car car);
    void SetWork(std::string work);
    void SetHours(std::string hours);
    void SetPrice(std::string price);

private:
    std::string m_date;
    Car m_car;
    std::string m_work;
    std::string m_hours;
    std::string m_price;
};

#endif // JOB_H
