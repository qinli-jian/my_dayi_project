#ifndef EQUIPMENT_H
#define EQUIPMENT_H


//#include"mainwindow.h"
//#include<QMap>
#include<QObject>
#include<QMainWindow>
class Equipment:public QObject{

    Q_OBJECT

public:

    Equipment(QString id,QString itime,QString la,QString lo,QString modelNumber,QString numOfMoni,int state,QMainWindow*p);
    void setNum(QString num);
    QString getInspectionNo();
    QString getID();
    QString getLO();
    QString getLA();
    QString getinstallTime();
    bool getState();
    void setLO(QString lo);
    void setLA(QString la);
    void setInspectionNo(QString No);
    //QMap<QString,QList<QString> > getData();

    int get_state();
    void set_state(int state);
    ~Equipment();
protected:

    QString la;
    QString lo;
    QString modelNumber;
    int state;
    QString inspectionPointNo;
    QString id;
    QString installtime;
};


#endif // EQUIPMENT_H
