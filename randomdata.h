#ifndef RANDOMDATA_H
#define RANDOMDATA_H

#include <QObject>
#include<QSqlDatabase>
#include<QTime>
#include<QSqlQuery>
#include<QDebug>
class RandomData : public QObject
{
    Q_OBJECT
public:
    explicit RandomData(QObject *parent = nullptr);
    void random_carData(QSqlDatabase&cardata,int n,QString inspectionPointNo);
    void random_peopleData(QSqlDatabase&peopledata,int n,QString inspectionPointNo,QString equipment);
signals:

public slots:

private:
    QString tmp;
    QStringList lp_list;
    QStringList color;
    int lp_len;
    int color_len;
};

#endif // RANDOMDATA_H
