#ifndef LICENSEPLATEMONITORING_H
#define LICENSEPLATEMONITORING_H
#include"mainwindow.h"
#include"widget.h"
class Widget;
class LicensePlateMonitoring:public Equipment{
Q_OBJECT
public:
    LicensePlateMonitoring(QString id,QString installTime,QString la,QString lo,QString modelNumber,QString inspectionPointNo,int state,QMainWindow*p);
    QString getid();
    ~LicensePlateMonitoring();
    //QMap<QString,QList<QString> > getData();
    friend class Widget;
private:
    Widget * licensePlat;
};

#endif // LICENSEPLATEMONITORING_H
