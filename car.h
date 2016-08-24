#ifndef CAR_H
#define CAR_H
#include <QString>
#include <QDataStream>

class Car
{
public:
    Car();
    ~Car();
    Car(QString year, QString make, QString model);
    QString GetYear() const;
    QString GetMake() const;
    QString GetModel()const;
    void SetYear(QString year);
    void SetMake(QString make);
    void SetModel(QString model);
private:
    QString m_year;
    QString m_make;
    QString m_model;

};
QDataStream &operator<<(QDataStream &out, const Car &car);
QDataStream &operator>>(QDataStream &in, Car &car);

#endif // CAR_H
