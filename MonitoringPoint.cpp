#include"MonitoringPoint.h"
MonitoringPoint::MonitoringPoint(QString id,QString la,QString lo,QString t){
    installtime=t;
    this->id=id;
    this->la=la;
    this->lo=lo;
}

 QString MonitoringPoint::getNum(){
     return id;
 }
 QString MonitoringPoint::getLa(){
     return la;
 }
 QString MonitoringPoint::getLo(){
     return lo;
 }

 QString MonitoringPoint::get_itime()
 {
     return installtime;
 }

 void MonitoringPoint::setNum(QString id)
 {
     this->id=id;
 }

 void MonitoringPoint::setLo(QString lo)
 {
     this->lo=lo;
 }

 void MonitoringPoint::setLa(QString la)
 {
     this->la=la;
 }
