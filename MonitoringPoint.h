#ifndef MONITORINGPOINT_H
#define MONITORINGPOINT_H
#include<QString>
#include<QObject>
#include"NTime.h"
#include"Equipment.h"
class MonitoringPoint:public QObject{
    Q_OBJECT
public:
    MonitoringPoint(QString id="00", QString la="00",QString lo="00",QString t="2021-01-01 00:00:00");

    QString getNum();
    QString getLa();
    QString getLo();
    QString get_itime();
    void setNum(QString id);
    void setLo(QString lo);
    void setLa(QString la);
private:
    QString la,lo;
    QString id;
    QString installtime;

};

#endif // MONITORINGPOINT_H
