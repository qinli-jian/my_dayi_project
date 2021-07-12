#include"Road.h"
#include"MonitoringPoint.h"
#include<QDebug>


Road:: Road( QString bla,QString blo,QString ela,QString elo){

    this->bla=bla;
    this->blo=blo;
    this->ela=ela;
    this->elo=elo;

}

void Road::setLatitudeAndLongitude( QString bla,QString blo,QString ela,QString elo){
    this->bla=bla;
    this->blo=blo;
    this->ela=ela;
    this->elo=elo;
}



QStringList Road::getBEla_BElo(){
    QStringList str;
    str<<bla<<blo<<ela<<elo;
    return str;
}


