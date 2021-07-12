#ifndef VIDEOSURVEILLANCE_H
#define VIDEOSURVEILLANCE_H
#include"mainwindow.h"
#include<QMap>
#include"dialog.h"
class Dialog;
class VideoSurveillance:public Equipment{
Q_OBJECT
public:
    VideoSurveillance(QString id,QString installTime,QString la,QString lo,QString modelNumber,QString numOfMoni,int state,QMainWindow*p);
    ~VideoSurveillance();
    //QMap<QString,QList<QString> > getData();
private:
    Dialog*video_face;
    MainWindow*p;

};

#endif // VIDEOSURVEILLANCE_H
