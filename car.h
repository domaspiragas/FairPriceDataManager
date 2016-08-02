#ifndef CAR_H
#define CAR_H
#include <QString>

class Car
{
public:
    Car();
    Car(QString year, QString make, QString model);
    QString GetYear();
    QString GetMake();
    QString GetModel();
    void SetYear(QString year);
    void SetMake(QString make);
    void SetModel(QString model);
private:
    QString m_year;
    QString m_make;
    QString m_model;
};

#endif // CAR_H
