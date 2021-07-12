#include "widget.h"
#include "ui_widget.h"
#include<QString>
#include<QDebug>

void Widget::closeEvent(QCloseEvent *event)
{
    timer->stop();
    qDebug()<<"close";
}

Widget::Widget(LicensePlateMonitoring *lp,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    p=(MainWindow*)parent;
    car_flow=p->get_carflowData();
    qDebug()<<"widget1111";
    lp_object=lp;
    qDebug()<<"widget2222";
    this->state=lp_object->get_state();
    qDebug()<<"widget4444  "<<this->state;
    ui->comboBox->setCurrentIndex(1-(this->state));

    ui->lineEdit_id->setText(lp_object->id);
    ui->lineEdit_lo->setText(lp_object->lo);
    ui->lineEdit_la->setText(lp_object->la);
    ui->lineEdit_inspection->setText(lp_object->inspectionPointNo);
    ui->label_time->setText(lp_object->installtime);
    qDebug()<<"widget3333";
    QDate d1(2021,4,25);
    QTime t1(0,0);
    QDate d2(2021,4,25);
    QTime t2(23,59);
    ui->time1->setDate(d1);
    ui->time1->setTime(t1);
    ui->time2->setDate(d2);
    ui->time2->setTime(t2);
    chart=new QChart();
    count = this->statistics();
    chart->addSeries(lineseries);
    chart->createDefaultAxes();
    QValueAxis * axisx = new QValueAxis;
    qDebug()<<"count"<<count;
    axisx->setRange(1,count);
    axisx->setTitleText(QString("The i-th %3 between  %1 and %2").arg(ui->time1->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->time2->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg("hour"));
    chart->setAxisX(axisx);
    ui->widget->setChart(chart);


    timer = new QTimer(this);                                        //创建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(DrawLine()));

}

LicensePlateMonitoring *Widget::get_lp_object()
{
    return lp_object;
}

int Widget::statistics()
{
    QDateTime d1=ui->time1->dateTime();
    QDateTime d2 =ui->time2->dateTime();
    qint64 di1 = d1.toSecsSinceEpoch();
    qint64 di2 = d2.toSecsSinceEpoch();
    qint64 res = di2-di1;
    if(res<=0){
        QMessageBox::warning(this,tr("warning"),tr("time error!"),QMessageBox::Ok);
        return 0;
    }
    qDebug()<<"tongji"<<res;
    lineseries=new QLineSeries;
    barseries=new QBarSeries;
    qint64 hours_s=60*60;//一小时的秒数
    count=(res+60)/hours_s;//有多少个小时
    QVector<int> s(count);
    QSqlQuery t(this->car_flow);
    t.exec(QString("select * from traffic where inspectionPointNo='%1';").arg(lp_object->getInspectionNo()));
    QDateTime temp;qint64 index_t;
    while (t.next()) {
        if(t.value(2).toString()!=lp_object->getInspectionNo())continue;
       temp=QDateTime::fromString(t.value(1).toString(),"yyyy-M-dd h:mm");
       if(temp.toSecsSinceEpoch()<=0){
           temp=QDateTime::fromString(t.value(1).toString(),"yyyy-M-dd hh:mm");
       }
       if(temp.toSecsSinceEpoch()<=0){
           temp=QDateTime::fromString(t.value(1).toString(),"yyyy-MM-dd h:mm");
       }
       if(temp.toSecsSinceEpoch()<=0){
           temp=QDateTime::fromString(t.value(1).toString(),"yyyy-MM-dd hh:mm");
       }
       //qDebug()<<temp.toSecsSinceEpoch();
       if(!(temp.toSecsSinceEpoch()>=di1&&di2>=temp.toSecsSinceEpoch()))continue;
       index_t=(temp.toSecsSinceEpoch()-di1)/hours_s;
       if(index_t>=count)continue;
       s[int(index_t)]++;
    }

    int j=1;
    QBarSet *s1=new QBarSet("car");
    for (QVector<int>::iterator it=s.begin();it!=s.end();it++) {
        qDebug()<<*it;
        lineseries->append(j++,*it);

        *s1<<(*it);
    }
    barseries->clear();
    barseries->append(s1);
    return count;
}

Widget::~Widget()
{
    timer->stop();
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    cardata_searchface care_data(p,this);

    care_data.exec();

}



void Widget::on_lineEdit_id_returnPressed()
{

}

void Widget::on_lineEdit_inspection_editingFinished()
{
    QString a=ui->lineEdit_inspection->text();
    qDebug()<<a;
    if(a==lp_object->inspectionPointNo){
        qDebug()<<"had same!";
        return;
    }
}

void Widget::on_comboBox_2_currentIndexChanged(int index)
{
    if(index==0){//line

        chart->removeAllSeries();
        int f=this->statistics();
        if(!f)return;
        chart->addSeries(lineseries);
        chart->createDefaultAxes();
        QValueAxis * axisx = new QValueAxis;
        axisx->setRange(1,count);
        qDebug()<<"count"<<count;
        axisx->setTitleText(QString("The i-th %3 between  %1 and %2").arg(ui->time1->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->time2->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg("hour"));
        chart->setAxisX(axisx);

    }else if(index==1){
        //bar
        chart->removeAllSeries();
        int f=this->statistics();
        if(!f)return;
        chart->addSeries(barseries);
        chart->createDefaultAxes();
        QValueAxis * axisx = new QValueAxis;
        axisx->setRange(1,count);
        axisx->setTitleText(QString("The i-th %3 between  %1 and %2").arg(ui->time1->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->time2->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg("hour"));
        chart->setAxisX(axisx);

    }
    qDebug()<<index;
}

void Widget::on_pushButton_4_clicked()
{
    if(ui->comboBox->currentIndex()==1){
        return;
    }

//    mchart=ui->widget->chart();
    initDraw();
    timer->start();
    timer->setInterval(2000);

}

void Widget::on_pushButton_5_clicked()
{
    if(lp_object->id==ui->lineEdit_id->text()&&lp_object->inspectionPointNo==ui->lineEdit_inspection->text()){
        return;
    }
    QSqlQuery t(p->get_equipmentData());//设备的数据库
    //if(p->get_equipmentModel()!=nullptr)
    QSqlTableModel *t_model=p->get_equipmentModel();
    if(lp_object->id!=ui->lineEdit_id->text()){
    t.exec(QString("select count(*) from equipment where id='%1';").arg(ui->lineEdit_id->text()));
    t.next();
    int count=t.value(0).toInt();
    qDebug()<<"ok"<<count;
    //QModelIndex e_index=p->get_quip_index();
    if(count==0){//没有相同的设备id
        t.exec(QString("update equipment set id='%1' where id='%2';").arg(ui->lineEdit_id->text()).arg(lp_object->id));
        lp_object->setNum(ui->lineEdit_id->text());
        qDebug()<<"gaimingzi";
    }else{
        ui->lineEdit_id->setText(lp_object->getid());
        if(!(lp_object->inspectionPointNo==ui->lineEdit_inspection->text()))
        QMessageBox::warning(this,tr("warning"),tr("Has same equipment id!"),QMessageBox::Ok);
    }
    }
    if(lp_object->inspectionPointNo!=ui->lineEdit_inspection->text()){
    QSqlQuery t_inspe(p->get_inspectionData());
    t_inspe.exec(QString("select count(*) from inspection where id='%1';").arg(ui->lineEdit_inspection->text()));
    t_inspe.next();
    int count2=t_inspe.value(0).toInt();
    qDebug()<<"ok2"<<count2;
    if(count2>0){//要有那个桩号才能改
        t.exec(QString("select count(*) from equipment where inspectionPointNo='%1' and kindName = 'License plate' ; ").arg(ui->lineEdit_inspection->text()));
        t.next();
        if(t.value(0).toInt()>=1){
            //已经有一个同样的了
            QMessageBox::warning(this,tr("warning"),tr("Target detection point full!"),QMessageBox::Ok);
            ui->lineEdit_inspection->setText(lp_object->getInspectionNo());
        }else{
        t.exec(QString("update equipment set inspectionPointNo='%1' where id='%2';").arg(ui->lineEdit_inspection->text()).arg(lp_object->id));

        lp_object->inspectionPointNo=ui->lineEdit_inspection->text();
        t_inspe.exec(QString("select * from inspection where id='%1';").arg(ui->lineEdit_inspection->text()));t_inspe.next();
        QString lo=t_inspe.value(2).toString();
        QString la=t_inspe.value(3).toString();
        lp_object->lo=lo;
        lp_object->la=la;
        ui->lineEdit_lo->setText(lo);
        ui->lineEdit_la->setText(la);
         t.exec(QString("update equipment set Longitude='%1' where id='%2';").arg(lo).arg(lp_object->id));
         t.exec(QString("update equipment set Latitude='%1' where id='%2';").arg(la).arg(lp_object->id));
    }
    }else{
        ui->lineEdit_inspection->setText(lp_object->inspectionPointNo);

        QMessageBox::warning(this,tr("warning"),tr("Has not this inspection!"),QMessageBox::Ok);
    }
    }
    if(t_model!=nullptr)
    t_model->submitAll();
}

void Widget::on_pushButton_2_clicked()
{
    chart->removeAllSeries();
    int f=this->statistics();
    if(!f)return;
    if(ui->comboBox_2->currentIndex()==0){
        chart->addSeries(lineseries);
    }else{
        chart->addSeries(barseries);
    }
    chart->createDefaultAxes();
    QValueAxis * axisx = new QValueAxis;
    axisx->setRange(1,count);
    qDebug()<<"count"<<count;
    axisx->setTitleText(QString("The i-th %3 between  %1 and %2").arg(ui->time1->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->time2->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg("hour"));
    chart->setAxisX(axisx);
}


void Widget::initDraw(){

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
    chart = new QChart();
    lineseries = new QLineSeries;
    axisX = new QDateTimeAxis();
    axisY = new QValueAxis();

    chart->legend()->hide();                             //隐藏图例
    chart->addSeries(lineseries);                            //把线添加到chart
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

    chart->addAxis(axisX,Qt::AlignBottom);               //设置坐标轴位于chart中的位置
    chart->addAxis(axisY,Qt::AlignLeft);

    lineseries->attachAxis(axisX);                           //把数据添加到坐标轴上
    lineseries->attachAxis(axisY);

    axisY->setTitleText("y1");

    //把chart显示到窗口上
    ui->widget->setChart(chart);
    ui->widget->setRenderHint(QPainter::Antialiasing);   //设置抗锯齿
}

void Widget::DrawLine(){
    if(ui->comboBox->currentIndex()==1){timer->stop();return;}
    int number;
    QDateTime currentTime = QDateTime::currentDateTime();
    //设置坐标轴显示范围
    chart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-60 * 1));       //系统当前时间的前一秒
    chart->axisX()->setMax(QDateTime::currentDateTime().addSecs(0));            //系统当前时间

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));                          //这里生成随机数做测试
    number = qrand() %25;//随机生成的值//一个值为n就是有n辆车过去，要生成n个数据
    RandomData r(this);
    r.random_carData(p->get_carflowData(),number,lp_object->getInspectionNo());
    //增加新的点到曲线末端
    lineseries->append(currentTime.toMSecsSinceEpoch(), number);
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    QSqlQuery t(p->get_equipmentData());
    t.exec(QString("update equipment set state=%1 where id='%2';").arg(QString::number(1-index)).arg(lp_object->getID()));
    state=1-index;
    lp_object->set_state(state);
    if(p->get_equipmentModel()!=nullptr)
    (p->get_equipmentModel())->submitAll();
}
