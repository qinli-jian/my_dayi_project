#include "randomdata.h"

RandomData::RandomData(QObject *parent) : QObject(parent)
{
    tmp="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    lp_list<<"京"<<"津"<<"翼"<<"桂"<<"渝"<<"沪"<<"辽"<<"吉"<<"苏"<<"粤";
    lp_len=10;
    color<<"黄"<<"蓝"<<"白"<<"黑"<<"绿";
    color_len=5;
}

void RandomData::random_peopleData(QSqlDatabase &peopledata, int n, QString inspectionPointNo, QString equipment)
{
    QSqlQuery q_people(peopledata);
    QTime t=QTime::currentTime();
    QString imei="";
    QString recordTime;
    qint64 cur_t;
    for(int i=0;i<n;i++){
        qsrand(t.msec()+t.second()*1000+i);
        for(int j=0;j<15;j++){
            imei+=tmp[qrand()%10];
        }
        //生成时间
        recordTime=QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss");
        cur_t=QDateTime::currentDateTime().toSecsSinceEpoch();
        qDebug()<<imei<<"|"<<recordTime<<"|"<<inspectionPointNo<<"|"<<equipment<<"|"<<cur_t;
        q_people.exec(QString("insert into passegerflow values('%1','%2','%3','%4',%5)").arg(imei,recordTime,inspectionPointNo,equipment,QString::number(cur_t)));
        imei="";
    }
}

void RandomData::random_carData(QSqlDatabase &cardata,int n,QString inspectionPointNo)
{
    QSqlQuery q_car(cardata);
    QTime t;
    t=QTime::currentTime();
    QString lp_str="";
    QString recoedTime;
    qint64 cur_t;
    double speed;
    for(int i=0;i<n;i++){//n条数据
        qsrand(t.msec()+t.second()*1000+i);
        lp_str+=color.at(qrand()%color_len);
        lp_str+=lp_list.at(qrand()%lp_len);
        for(int j=0;j<6;j++){
            lp_str+=tmp[qrand()%tmp.length()];//生成了六个数字与字母组合
        }
        //车牌生成完毕

        //生成时间
        recoedTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        cur_t=QDateTime::currentDateTime().toSecsSinceEpoch();
        //所在的检测点编号

        //生成速度
        speed=(double(qrand()%10000))/100;

        //时间戳
        qDebug()<<lp_str<<"|"<<recoedTime<<"|"<<inspectionPointNo<<"|"<<speed<<"|"<<cur_t;
        q_car.exec(QString("insert into traffic values('%1','%2','%3',%4,%5)").arg(lp_str).arg(recoedTime).arg(inspectionPointNo).arg(QString::number(speed)).arg(QString::number(cur_t)));
        lp_str="";
    }
}
