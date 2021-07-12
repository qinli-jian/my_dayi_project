#ifndef NTIME_H
#define NTIME_H

#include"mainwindow.h"
#include<QObject>

class NTime:public QObject{
    Q_OBJECT
private:
    QString year,month,day,hour,minute,second;
public:
    NTime(QString y=0,QString m=0,QString d=0,QString h=0,QString mi=0,QString s=0);
    NTime(QDateTime time);
    NTime(QString time);
    NTime(NTime &t);
    void setTime(QString y,QString m,QString d,QString h,QString mi,QString s);
    void setTime(QDateTime time);
    void setTime(QString time);
    void set(QString arg,int index);
    bool legitimate(QString arg,int intdex);
    bool leap(QString year);
    QString getTimeToStr();
    QDateTime getTime();
    ~NTime();
};

#endif // NTIME_H
