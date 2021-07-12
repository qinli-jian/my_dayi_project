#include "cardata_searchface.h"
#include "ui_cardata_searchface.h"
#include"readonlyClass.h"
#include <QStandardItemModel>
#include<QDebug>
cardata_searchface::cardata_searchface(MainWindow*p1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cardata_searchface)
{
    qDebug()<<"in side";
    ui->setupUi(this);
    p_main=p1;
    p_prode=((Widget*)parent)->get_lp_object();
    QSqlDatabase& lince_datat=p_main->get_carflowData();
    QSqlQuery q_car(lince_datat);
    q_car.exec(QString("select * from traffic where inspectionPointNo='%1';").arg(p_prode->getInspectionNo()));
    qDebug()<<p_prode->getInspectionNo();
    model = new QSqlTableModel(this,lince_datat);
    model->setTable("traffic");
    model->select();
    qDebug()<<p_prode->getid();
    //model->insertRowIntoTable()
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
    model->setFilter(QString("inspectionPointNo='%1'").arg(p_prode->getInspectionNo()));
    model->select();
    int n=4;
    ReadOnlyDelegate*readOnly=new ReadOnlyDelegate();
    for (int i=0;i<n;i++) {
        ui->tableView->setItemDelegateForColumn(i,readOnly);
        ui->tableView->setColumnWidth(i,300);
    }



}

cardata_searchface::~cardata_searchface()
{
    delete ui;
}





void cardata_searchface::on_pushButton_clicked()
{
    QString lp_str=" ";
    if(ui->lineEdit->text().isEmpty()){

        model->setFilter(QString("inspectionPointNo='%1'").arg(p_prode->getInspectionNo()));
        model->select();
        return;
    }
//    QSqlQuery t(p_main->get_carflowData());
//    t.exec(QString("select * from traffic where inspectionPointNo='%1';").arg(p_prode->getInspectionNo()));
//    QString t_str;
//    int f=0;
//    QString ans_str;
//    while (t.next()) {
//        if(ui->lineEdit->text()=="NO"){
//            f=1;
//            lp_str=ui->lineEdit->text()+'\n';break;
//        }
//        t_str=t.value(0).toString();
//        lp_str=t_str;
//        ans_str=t_str.right(t_str.length()-1);
//        qDebug()<<ans_str;
//        if(ans_str==(ui->lineEdit->text()+"\n")){
//            f=1;
//            qDebug()<<"in";
//            break;
//        }

//    }

//    QString lincepl=ui->lineEdit->text();
//    qDebug()<<lincepl;
//    qDebug()<<"+++"<<lp_str;
//    if(f==0){
//        lp_str=" ";
//    }
//    qDebug()<<"---"<<lp_str;
//    ui->tableView->setModel(model);
    this->model->setFilter(tr("licensePlate like '%%1%' AND inspectionPointNo='%2'").arg(ui->lineEdit->text()).arg(p_prode->getInspectionNo()));
    model->select();
}

void cardata_searchface::on_tableView_clicked(const QModelIndex &index)
{
    QString t=((model->data(index)).toString());
    t=t.left(1);
    qDebug()<<t;
}

void cardata_searchface::on_pushButton_2_clicked()
{

    QDateTime d1=ui->dateTimeEdit_t1->dateTime();
    QDateTime d2=ui->dateTimeEdit_t2->dateTime();
    if(d1.toSecsSinceEpoch()>d2.toSecsSinceEpoch()){
        QMessageBox::warning(this,tr("warning"),tr("time error"),QMessageBox::Ok);
        return;
    }

    QSqlQuery t(p_main->get_carflowData());

 //   QDateTime tdt;
 //   while (t.next()) {
//        tdt=QDateTime::fromString(t.record().value(1).toString(),"yyyy-M-dd h:mm");
//        if(tdt.toSecsSinceEpoch()<=0){
//            tdt=QDateTime::fromString(t.record().value(1).toString(),"yyyy-MM-dd h:mm");
//        }
//        if(tdt.toSecsSinceEpoch()<=0){
//            tdt=QDateTime::fromString(t.record().value(1).toString(),"yyyy-M-dd hh:mm");
//        }
//        if(tdt.toSecsSinceEpoch()<=0){
//            tdt=QDateTime::fromString(t.record().value(1).toString(),"yyyy-MM-dd hh:mm");
//        }
//        if(tdt.toSecsSinceEpoch()>=d1.toSecsSinceEpoch()&&tdt.toSecsSinceEpoch()<=d2.toSecsSinceEpoch()){
 //           QString str=t.record().value(1).toString();
            //qDebug()<<str;
           model->setFilter(QString("TimeStamp>=%1 AND TimeStamp<=%2 AND inspectionPointNo='%3'").arg(QString::number(d1.toSecsSinceEpoch())).arg(QString::number(d2.toSecsSinceEpoch())).arg(p_prode->getInspectionNo()));
//            model->select();
//           model->setFilter(QString("inspectionPointNo='%1").arg(p_prode->getInspectionNo()));
            //modelbytime->insertRecord(count_r++,t.record());
//        }
       t.exec(QString("select * from traffic where inspectionPointNo='%1'and TimeStamp>=%2 and TimeStamp<=%3;").arg(p_prode->getInspectionNo()).arg(QString::number(d1.toSecsSinceEpoch())).arg(QString::number(d2.toSecsSinceEpoch())));


        model->select();
  //  }

    //ui->tableView->setModel(modelbytime);

}

void cardata_searchface::on_pushButton_3_clicked()
{
    double d1=ui->doubleSpinBox->value(),d2=ui->doubleSpinBox_2->value();
    if(d1>d2){
        QMessageBox::warning(this,tr("warning"),tr("speed error!"),QMessageBox::Ok);
        return;
    }

    model->setFilter(QString("speed>=%1 AND speed<=%2 AND inspectionPointNo='%3' ").arg(QString::number(d1)).arg(QString::number(d2)).arg(p_prode->getInspectionNo()));
    model->select();

}

void cardata_searchface::on_comboBox_currentIndexChanged(int index)
{
    if(index==1){
        //升序
        model->setSort(3,Qt::AscendingOrder);
        model->select();
    }else if(index==2){
        model->setSort(3,Qt::DescendingOrder);
        model->select();
    }
}
