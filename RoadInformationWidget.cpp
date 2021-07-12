#include"RoadInformationWidget.h"
#include<QFont>
#include<QFile>
RoadInformationWidget::RoadInformationWidget(QWidget*p):QDialog(p){
   QDialog::setMinimumSize(800,800);
   QDialog::setMaximumSize(800,1000);
    roadNameLabel=new QLabel("The Road Name:",this);
    roadName = new QLabel("WuYi Highway",this);

    beginNameLabel=new QLabel("Starting Point:",this);
    beginName=new QLabel("WuDing County",this);


    endNameLabel=new QLabel("End:",this);
    endName=new QLabel("YiMeng County",this);

    beginLAL=new QLabel("(123.456E,123.987S)",this);
    beginLALLabel = new QLabel("Latitude And Longitude Of Starting Point:",this);


    endLAL = new QLabel("(103.123E,146.98S)",this);
    endLALLabel = new QLabel("Latitude And Longitude Of End:",this);

    infoTitle=new QLabel("Introduction To The Expressway",this);
    detailedIntroduction = new QTextEdit(this);

    roadNameLabel->move(50,50);
    roadName->move(200,50);

    beginNameLabel->move(50,100);
    beginName->move(200,100);
    beginLALLabel->move(50,150);
    beginLAL->move(400,150);

    endNameLabel->move(50,200);
    endName->move(200,200);

    endLALLabel->move(50,250);
    endLAL->move(400,250);

    infoTitle->move(200,350);
    QFont *f = new QFont;
    f->setFamily("Calibri");
    f->setPixelSize(30);
    f->setBold(true);
    infoTitle->setFont(*f);
    detailedIntroduction->move(50,400);

    QFile data("../dayi_project_20210519/textData/informationofhightway.txt");
    QString  textData="";

    if(data.open(QFile::ReadOnly|QIODevice::Text)){
        QTextStream in(&data);
        while (!in.atEnd()) {
            textData+=in.readLine()+'\n';
            qDebug()<<in.readLine();
        }
    }
    qDebug()<<textData;
    detailedIntroduction->setReadOnly(true);
    detailedIntroduction->resize(700,550);
    detailedIntroduction->setText(textData);

    detailedIntroduction->setText(textData);
    QFont textf("Yu Gothic Medium",10);
    detailedIntroduction->setFont(textf);

}

RoadInformationWidget::~RoadInformationWidget(){

}
