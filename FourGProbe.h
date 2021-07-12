#ifndef FOURGPROBE_H
#define FOURGPROBE_H
#include"mainwindow.h"
#include"widget.h"
#include"Equipment.h"
#include"fourgfacing.h"
class fourGfacing;
class MainWindow;
class Widget;
class FourGProbe:public Equipment{
Q_OBJECT
public:
    FourGProbe(QString id,QString installTime,QString la,QString lo,QString modelNumber,QString inspectionPointNo,int state,QMainWindow*p);
    ~FourGProbe();
    QString getid();


private:

    MainWindow * p;
    fourGfacing*fourGinterface;
};

#endif // FOURGPROBE_H
