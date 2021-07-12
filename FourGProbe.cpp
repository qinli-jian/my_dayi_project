#include"FourGProbe.h"

FourGProbe::FourGProbe(QString id,QString installTime,QString la,QString lo,QString modelNumber,QString inspectionPointNo,int state,QMainWindow*p):Equipment(id,installTime,la,lo,modelNumber,inspectionPointNo,state,p)
{
    qDebug()<<"create four object";
    this->p=(MainWindow*)p;
    fourGinterface=new fourGfacing(this->p,this);
    fourGinterface->setWindowTitle(tr("Four G Prode"));
    fourGinterface->exec();
    delete fourGinterface;
}

FourGProbe::~FourGProbe(){

}

QString FourGProbe::getid()
{
    return id;
}
