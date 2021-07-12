#include"Equipment.h"


Equipment::Equipment(QString id,QString itime,QString la,QString lo,QString modelNumber,QString numOfMoni,int state,QMainWindow*p):QObject(p){
    installtime=itime;
    this->la=la;
    this->lo=lo;
    this->modelNumber=modelNumber;
    this->inspectionPointNo=numOfMoni;
    this->id=id;
    this->state=state;
}
void Equipment::setNum(QString num){
     this->id=num;
}


QString Equipment::getInspectionNo()
{
    return this->inspectionPointNo;
}

QString Equipment::getID()
{
    return id;
}

QString Equipment::getLO()
{
    return lo;
}

QString Equipment::getLA()
{
    return la;
}

QString Equipment::getinstallTime()
{
    return installtime;
}
bool Equipment::getState(){
    return 1;
}

void Equipment::setLO(QString lo)
{
    this->lo=lo;
}

void Equipment::setLA(QString la)
{
    this->la=la;
}

void Equipment::setInspectionNo(QString No)
{
    inspectionPointNo=No;
}
//QMap<QString,QList<QString> > getData();


int Equipment::get_state()
{
    return state;
}

void Equipment::set_state(int state)
{
  this->state=state;
}
Equipment::~Equipment(){

}
