#include"NTime.h"
#include<QMessageBox>
NTime::NTime(QString y,QString m,QString d,QString h,QString mi,QString s){
    year=y;
    month=m;
    day=d;
    hour=h;
    minute=mi;
    second=s;

}

NTime::NTime(QDateTime time){
    setTime(time);
}
NTime::NTime(QString time){
    setTime(time);
}

void NTime::setTime(QString y,QString m,QString d,QString h,QString mi,QString s){
    set(y,1);
    set(m,2);
    set(d,3);
    set(h,4);
    set(mi,5);
    set(s,6);
}

void NTime::set(QString arg, int index){
    if(!legitimate(arg,index)) return;
    switch (index) {
    case 1:year=arg;break;
    case 2:month=arg;break;
    case 3:day=arg;break;
    case 4:hour=arg;break;
    case 5:minute=arg;break;
    case 6:second=arg;break;
    default:
        QMessageBox::critical(nullptr,"critical message","This index is illegal!",QMessageBox::Ok|QMessageBox::Default);
        return;
    }
}

bool NTime::legitimate(QString arg, int index){

    switch (index) {
    case 1:{
        if(!(arg.toInt() >=1000&&arg.toInt()<=3000)){
            QMessageBox::critical(nullptr,"critical message","This year's value is illegal!",QMessageBox::Ok|QMessageBox::Default);
            return 0;
        }
    }break;
    case 2:{
        if(!(arg.toInt()>=1&&arg.toInt()<=12)){
            QMessageBox::critical(nullptr,"critical message","This month's value is illegal!",QMessageBox::Ok|QMessageBox::Default);
             return 0;
        }
    }break;
    case 3:{
        int monthDay[12]={31,28,31,30,31,30,31,31,30,31,30,31};
        if(!((!leap(year)&&arg.toInt()>=1&&arg.toInt()<=monthDay[month.toInt()])&&leap(year)&&arg.toInt()>=1&&arg.toInt()<=(monthDay[month.toInt()]+(month.toInt()==2)))){
            QMessageBox::critical(nullptr,"critical message","This day's value is illegal!",QMessageBox::Ok|QMessageBox::Default);
            return 0;
        }
    }break;
    case 4:{
        if(!(arg.toInt()>=0&&arg.toInt()<=23)){
            QMessageBox::critical(nullptr,"critical message","This hour's value is illegal!",QMessageBox::Ok|QMessageBox::Default);
            return 0;
        }
    }break;
    case 5:{
        if(!(arg.toInt()>=0&&arg.toInt()<=59)){
            QMessageBox::critical(nullptr,"critical message","This minute's value is illegal!",QMessageBox::Ok|QMessageBox::Default);
            return 0;
        }
    }break;
    case 6:{
        if(!(arg.toInt()>=0&&arg.toInt()<=59)){
                QMessageBox::critical(nullptr,"critical message","This second's value is illegal!",QMessageBox::Ok|QMessageBox::Default);
                return 0;
        }
    }break;
    }
    return 1;
}

bool NTime::leap(QString year){
    if((year.toInt()%4==0&&year.toInt()%100!=0)||(year.toInt()%400==0)){
        return 1;
    }
    return 0;
}

NTime::~NTime(){

}

void NTime::setTime(QString time){

    QString s1 = time.mid(0,10);
    QString s2 = time.mid(11,18);
    QStringList date= s1.split("-");
    QStringList t = s2.split(":");
    year=date[0];
    month=date[1];
    day=date[2];
    hour=t[0];
    minute=t[1];
    second=t[2];

    qDebug()<<date<<t;

}

void NTime::setTime(QDateTime time){
    QString t = time.toString("yyyy-MM-dd h:m:s");
    setTime(t);
}

NTime::NTime( NTime &t){
    setTime(t.getTimeToStr());
}

QString NTime::getTimeToStr(){
    QString t=QString("%1-%2-%3 %4:%5:%6").arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second);
    return t;
}
