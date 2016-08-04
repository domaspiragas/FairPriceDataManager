#ifndef JOB_H
#define JOB_H
#include "car.h"
#include <QString>

class Job
{
public:
    Job(QString date, Car* car, QString work, QString hours, QString price);
    ~Job();
    QString GetDate();
    Car* GetCar();
    QString GetWork();
    QString GetHours();
    QString GetPrice();
    void SetDate(QString date);
    void SetCar(Car* car);
    void SetWork(QString work);
    void SetHours(QString hours);
    void SetPrice(QString price);

private:
    QString m_date;
    Car* m_car;
    QString m_work;
    QString m_hours;
    QString m_price;
};

#endif // JOB_H
