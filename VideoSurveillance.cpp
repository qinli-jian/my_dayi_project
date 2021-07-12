#include"VideoSurveillance.h"
VideoSurveillance::VideoSurveillance(QString id,QString installTime,QString la,QString lo,QString modelNumber,QString numOfMoni,int state,QMainWindow*p):Equipment(id,installTime,la,lo,modelNumber,numOfMoni,state,p){
    this->p=(MainWindow*)p;
    video_face=new Dialog(this,p);
    video_face->setWindowTitle(tr("Monitoring Equipment"));
    video_face->exec();
    delete video_face;
}

VideoSurveillance::~VideoSurveillance(){

}
