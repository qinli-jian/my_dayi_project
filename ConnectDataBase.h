#ifndef CONNECTDATABASE_H
#define CONNECTDATABASE_H

#include"mainwindow.h"

//static bool ConnectDataBase(){

//    QFile file("../dayi_project_20210519/p.csv"); //打开csv文件

//    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
//        QMessageBox::critical(nullptr,"Cannot open inspectionpoint database11!","Unable to establish a database connection.",QMessageBox::Cancel);
//        return false;
//    }
////-------------------------------------------------------------------****************************--------------------------------------------------------------------------
//    QSqlDatabase inspectionPointData = QSqlDatabase::addDatabase("QSQLITE","inspectionpoint");
//    inspectionPointData.setDatabaseName("inspectionpointdata.db");
//    if(!inspectionPointData.open()){
//        QMessageBox::critical(nullptr,"Cannot open inspectionpoint database22!","Unable to establish a database connection.",QMessageBox::Cancel);
//        return false;
//    }

//    //QSqlQuery q1(inspectionPointData);

//    //QSqlQuery sql_query(inspectionPointData);

////    if(!q1.exec("create table inspectionpoint(IMEI varchar(30) primary key,time varchar(30),station varchar(20),num varchar(20));")){
////        qDebug()<<"create error!!!";
////    }
////    QStringList list;
////    list.clear();
////    QTextStream in(&file);
////    //int acount=0;
////    QString t;
////    t= in.readLine();
////    t= in.readLine();
////    while (!in.atEnd()) {
////        QString fileLLine = in.readLine();
////        list = fileLLine.split(",",QString::SkipEmptyParts);
////        qDebug()<<list.at(0);

////        if(!q1.exec("insert into inspectionpoint(IMEI,time,station,num) values('"+QString(list.at(3))+"','"+QString(list.at(0)) +"','"+QString(list.at(1))+"','"+QString(list.at(2))+"');")){
////                qDebug()<<"insert error!!!";
////    }

////}



//    return true;
//}


#endif // CONNECTDATABASE_H
