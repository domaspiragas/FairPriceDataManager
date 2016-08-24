#ifndef JOB_H
#define JOB_H
#include "car.h"
#include <QString>
#include <QDataStream>

class Job
{
public:
    Job();
    Job(QString date, Car* car, QString work, QString hours, QString price);
    ~Job();
    QString GetDate() const;
    Car* GetCar() const;
    QString GetWork() const;
    QString GetHours() const;
    QString GetPrice() const;
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

QDataStream &operator<<(QDataStream &out, const Job &job);
QDataStream &operator>>(QDataStream &in, Job &job);
#endif // JOB_H
