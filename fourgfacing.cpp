#include "fourgfacing.h"
#include "ui_fourgfacing.h"

void fourGfacing::closeEvent(QCloseEvent*event)
{
    qDebug()<<"close";
    timer->stop();
    delete timer;
}

fourGfacing::fourGfacing(QMainWindow*parent,FourGProbe *four_onject) :
    QDialog(parent),
    ui(new Ui::fourGfacing)
{
    ui->setupUi(this);
    this->p=(MainWindow*)parent;
    this->four_onject=four_onject;
    this->state=four_onject->get_state();
    ui->comboBox_statu->setCurrentIndex(1-state);
    ui->lineEdit_id->setText(four_onject->getid());
    ui->lineEdit_inspection->setText(four_onject->getInspectionNo());
    ui->lineEdit_lo->setText(four_onject->getLO());
    ui->lineEdit_la->setText(four_onject->getLA());
    QDate d1(2021,04,26);
    QTime t1(0,0);
    QDate d2(2021,04,26);
    QTime t2(23,59);
    ui->dateTimeEdit->setDateTime(QDateTime(d1,t1));
    ui->dateTimeEdit_2->setDateTime(QDateTime(d2,t2));
   chart_t=new QChart();
   statistics();
   chart_t->addSeries(lineseries);
   chart_t->createDefaultAxes();
   QValueAxis *axis_x=new QValueAxis(this);
   axis_x->setRange(1,x_count);
   axis_x->setTitleText(QString("The i-th %3 between  %1 and %2").arg(ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg("hour"));
   chart_t->setAxisX(axis_x);
   ui->widget->setChart(chart_t);

   timer = new QTimer(this); //创建定时器
   connect(timer,SIGNAL(timeout()),this,SLOT(DrawLine()));
}

fourGfacing::~fourGfacing()
{
    //timer->stop();
    //disconnect(timer,SIGNAL(timeout()),this,SLOT(DrawLine()));
    //delete timer;
    delete ui;
}



void fourGfacing::statistics()
{

    QDateTime d1=ui->dateTimeEdit->dateTime();
    QDateTime d2=ui->dateTimeEdit_2->dateTime();
    if(d1.toSecsSinceEpoch()>=d2.toSecsSinceEpoch()){
        QMessageBox::warning(this,tr("warning"),tr("Time error!"),QMessageBox::Ok);
        return;
    }
    qDebug()<<"in in in"<<four_onject->getID();
    QSqlQuery people_q(p->get_peopleflowData());
    qint64 t1=d1.toSecsSinceEpoch();
    qint64 t2=d2.toSecsSinceEpoch();
    int jiange=60*60;//一个小时的秒数
    x_count=(t2-t1)/jiange+1;
    lineseries=new QLineSeries();
    barseries=new QBarSeries();

    QVector<int>count_v(x_count);
    lineseries->clear();
    qint64 ans_t;
    people_q.exec(QString("select * from passegerflow where equipmentid ='%1';").arg(four_onject->getID()));
    QString t;QStringList t_list;
    while (people_q.next()) {

        ans_t=people_q.value(4).toInt();
//        qDebug()<<ans_t;
        if(ans_t>=t1&&ans_t<=t2){
            count_v[int((ans_t-t1)/jiange)]++;//统计某个时间段的人次;

        }



    }
    int j=1;
    QBarSet *set_y=new QBarSet("people");
    for (QVector<int>::iterator i=count_v.begin() ;i!=count_v.end();i++,j++) {
        lineseries->append(j,*i);
        *set_y<<*i;
    }
    barseries->clear();
    barseries->append(set_y);
    qDebug()<<x_count;
    qDebug()<<"statistic finish";

}

void fourGfacing::fourGfacing::initDraw()
{
    QPen penY(Qt::darkBlue,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
//    delete chart;
//    chart = new QChart();
//    axisX = new QDateTimeAxis();
//    axisX->setFormat("hh:mm:ss");
//    axisX->setTitleText("实时时间");
//    axisX->setLinePen(penY);
//    lineseries->clear();
//    lineseries->attachAxis(axisX);
//    ui->widget->setChart(chart);

    //++++++++++++++++++++

    //QPen penY(Qt::darkBlue,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    chart_t = new QChart();
    lineseries = new QLineSeries;
    axisX = new QDateTimeAxis();
    axisY = new QValueAxis();

    chart_t->legend()->hide();                             //隐藏图例
    chart_t->addSeries(lineseries);                            //把线添加到chart
    axisX->setTickCount(10);                             //设置坐标轴格数
    axisY->setTickCount(5);
    axisX->setFormat("hh:mm:ss");                        //设置时间显示格式
    axisY->setMin(0);                                    //设置Y轴范围
    axisY->setMax(25);
    axisX->setTitleText("实时时间");                       //设置X轴名称
    axisY->setLinePenColor(QColor(Qt::darkBlue));        //设置坐标轴颜色样式
    axisY->setGridLineColor(QColor(Qt::darkBlue));
    axisY->setGridLineVisible(false);                    //设置Y轴网格不显示
    axisY->setLinePen(penY);
    axisX->setLinePen(penY);

    chart_t->addAxis(axisX,Qt::AlignBottom);               //设置坐标轴位于chart中的位置
    chart_t->addAxis(axisY,Qt::AlignLeft);

    lineseries->attachAxis(axisX);                           //把数据添加到坐标轴上
    lineseries->attachAxis(axisY);

    axisY->setTitleText("y1");

    //把chart显示到窗口上
    ui->widget->setChart(chart_t);
    ui->widget->setRenderHint(QPainter::Antialiasing);   //设置抗锯齿
}

void fourGfacing::on_pushButton_3_clicked()
{
    QString id_l=ui->lineEdit_id->text();
    QString inspection_id=ui->lineEdit_inspection->text();
    qDebug()<<inspection_id;
    if(id_l==four_onject->getID()&&inspection_id==four_onject->getInspectionNo()||ui->lineEdit_id->text().isEmpty()||ui->lineEdit_inspection->text().isEmpty()){
        qDebug()<<"not change!";
        return;
    }
    QSqlQuery equipment_t(p->get_equipmentData());
    if(id_l!=four_onject->getID()){
        equipment_t.exec(QString("select count(*) from equipment where id='%1';").arg(ui->lineEdit_id->text()));equipment_t.next();
        if(equipment_t.value(0).toInt()>=1){
            //说明有一样的的设备编号
            QMessageBox::warning(this,tr("warning"),tr("has same equipment ID!"),QMessageBox::Ok);
            qDebug()<<"has same ID";
        }else{
            //修改了数据库中该设备的id
            equipment_t.exec(QString("update equipment set id = '%1' where id='%2';").arg(ui->lineEdit_id->text()).arg(four_onject->getID()));
            four_onject->setNum(id_l);
            qDebug()<<"id change finish";
        }
    }

    if(inspection_id!=four_onject->getInspectionNo()){
        QSqlQuery inspection_q(p->get_inspectionData());
        inspection_q.exec(QString("select count(*) from inspection where id='%1';").arg(ui->lineEdit_inspection->text()));//查找是否有输入的检测点的ID
        inspection_q.next();
        int count_spection=inspection_q.value(0).toInt();
        qDebug()<<count_spection;

        if(count_spection>=1){
            //说明有输入的检测点
            qDebug()<<four_onject->getInspectionNo();
             equipment_t.exec(QString("select count(*) from equipment where inspectionPointNo='%1' and kindName='4G prode';").arg(inspection_id));
             equipment_t.next();
             int count_equip=equipment_t.value(0).toInt();
             qDebug()<<count_equip;
             if(count_equip==0){//没有相同的设备在同一检测点则增加
                 //获取该检测点的经度 纬度
                 inspection_q.exec(QString("select * from inspection where id='%1';").arg(inspection_id));inspection_q.next();
                 QString lo=inspection_q.value(2).toString();
                 QString la=inspection_q.value(3).toString();
                 //先是修改了数据库中设备的经纬度
                 equipment_t.exec(QString("update equipment set Longitude = '%1' where id='%2';").arg(lo).arg(four_onject->getID()));
                 equipment_t.exec(QString("update equipment set Latitude = '%1' where id='%2';").arg(la).arg(four_onject->getID()));
                 ui->lineEdit_lo->setText(lo);
                 ui->lineEdit_la->setText(la);
                 four_onject->setLO(lo);
                 four_onject->setLA(la);
                 //修改数据库中设备的所在的检测点的编号
                 equipment_t.exec(QString("update equipment set inspectionPointNo = '%1' where id='%2';").arg(inspection_id).arg(four_onject->getID()));
                 four_onject->setInspectionNo(inspection_id);

                 qDebug()<<"change inspection finish!";
             }else{
                 QMessageBox::warning(this,tr("warning"),tr("Target detection point full!"),QMessageBox::Ok);
                 ui->lineEdit_inspection->setText(four_onject->getInspectionNo());
             }

        }else{
            QMessageBox::warning(this,tr("warning"),tr("not this inspection!"),QMessageBox::Ok);
            ui->lineEdit_inspection->setText(four_onject->getInspectionNo());
        }
    }
    (p->get_equipmentModel())->submitAll();
}

void fourGfacing::DrawLine()
{
    if(ui->comboBox_statu->currentIndex()==1){timer->stop();return;}
    int number;
    QDateTime currentTime = QDateTime::currentDateTime();
    //设置坐标轴显示范围
    chart_t->axisX()->setMin(QDateTime::currentDateTime().addSecs(-60 * 1));       //系统当前时间的前一秒
    chart_t->axisX()->setMax(QDateTime::currentDateTime().addSecs(0));            //系统当前时间

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));                          //这里生成随机数做测试
    number = qrand() %25;//随机生成的值
    RandomData r(this);
    r.random_peopleData(p->get_peopleflowData(),number,this->four_onject->getInspectionNo(),four_onject->getID());
    //增加新的点到曲线末端
    lineseries->append(currentTime.toMSecsSinceEpoch(), number);
}

void fourGfacing::on_comboBox_2_currentIndexChanged(int index)
{
    if(index==0){
        //line
        chart_t->removeAllSeries();
        statistics();
        chart_t->addSeries(lineseries);
        chart_t->createDefaultAxes();
        QValueAxis *axis_x=new QValueAxis(this);
        axis_x->setRange(1,x_count);
        axis_x->setTitleText(QString("The i-th %3 between  %1 and %2").arg(ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg("hour"));
        chart_t->setAxisX(axis_x);
        ui->widget->setChart(chart_t);
    }else{
        chart_t->removeAllSeries();
        statistics();
        chart_t->addSeries(barseries);
        chart_t->createDefaultAxes();
        QValueAxis *axis_x=new QValueAxis(this);
        axis_x->setRange(1,x_count);
        axis_x->setTitleText(QString("The i-th %3 between  %1 and %2").arg(ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg("hour"));
        chart_t->setAxisX(axis_x);
        ui->widget->setChart(chart_t);
    }
}

void fourGfacing::on_pushButton_2_clicked()
{
    int index=ui->comboBox_2->currentIndex();
    on_comboBox_2_currentIndexChanged(index);
}

void fourGfacing::on_pushButton_4_clicked()
{
    initDraw();
    timer->start();
    timer->setInterval(2000);
}

void fourGfacing::on_pushButton_clicked()
{
    p_widget=new people_search(this->four_onject,p);
    p_widget->exec();
}

void fourGfacing::on_comboBox_statu_currentIndexChanged(int index)
{
    QSqlQuery t(p->get_equipmentData());
    t.exec(QString("update equipment set state=%1 where id='%2';").arg(QString::number(1-index)).arg(four_onject->getID()));
    state=1-index;
    four_onject->set_state(state);
    if(p->get_equipmentModel())
    (p->get_equipmentModel())->submitAll();
}
