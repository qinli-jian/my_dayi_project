#include"LicensePlateMonitoring.h"
#include"mainwindow.h"
LicensePlateMonitoring::LicensePlateMonitoring(QString id,QString installTime,QString la,QString lo,QString modelNumber,QString inspectionPointNo,int state,QMainWindow*p):Equipment(id,installTime,la,lo,modelNumber,inspectionPointNo,state,p){
    this->id=id;
    this->installtime=installTime;
    this->la=la;
    this->lo=lo;

    this->modelNumber=modelNumber;
    this->inspectionPointNo=inspectionPointNo;
    qDebug()<<"in object!!!1111";
    this->licensePlat=new Widget(this,p);
    qDebug()<<"in object!!!";
    licensePlat->setWindowTitle("License Plate");
    licensePlat->setWindowTitle(tr("Vehicle Identification Device"));
    licensePlat->exec();
    delete licensePlat;
}

QString LicensePlateMonitoring::getid()
{
    return this->id;
}

LicensePlateMonitoring::~LicensePlateMonitoring(){

}
