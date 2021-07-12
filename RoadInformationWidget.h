#ifndef ROADINFORMATIONWIDGET_H
#define ROADINFORMATIONWIDGET_H
#include"mainwindow.h"
#include<QTextEdit>
class RoadInformationWidget:public QDialog{
    Q_OBJECT
public:
    RoadInformationWidget(QWidget*p=nullptr);
    ~RoadInformationWidget();
private:
    QLabel *roadName,*roadNameLabel, *beginName,*beginNameLabel, *beginLAL,*beginLALLabel, *endName, *endNameLabel,*endLAL,*endLALLabel,*infoTitle;
    QTextEdit *detailedIntroduction;
};

#endif // ROADINFORMATIONWIDGET_H
