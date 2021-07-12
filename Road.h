#ifndef ROAD_H
#define ROAD_H

#include"mainwindow.h"
#include"MonitoringPoint.h"
class MonitoringPoint;

class Road:public QObject{
    Q_OBJECT
public:
    Road(QString bla="00",QString blo="00",QString ela="00",QString elo="00");
    void setNum(QString num);
    void setLatitudeAndLongitude(QString bla,QString blo,QString ela,QString elo);

    QStringList getBEla_BElo();
private:
    QString bla,blo,ela,elo;

public slots:
};

#endif // ROAD_H
