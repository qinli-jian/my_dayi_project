#include "people_search.h"
#include "ui_people_search.h"
#include"readonlyClass.h"
people_search::people_search(FourGProbe*p_prode,MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::people_search)
{
    ui->setupUi(this);
    this->p_prode=p_prode;
    p_main=parent;
    p_da=p_main->get_peopleflowData();
    QSqlQuery t(p_da);
    t.exec(QString("select * from passegerflow where equipmentid='%1';").arg(p_prode->getID()));
    people_model=new QSqlTableModel(this,p_da);
    ui->tableView->setModel(people_model);
    people_model->setTable("passegerflow");
    people_model->setFilter(QString("equipmentid='%1'").arg(p_prode->getID()));
    people_model->select();

    ReadOnlyDelegate *read_only=new ReadOnlyDelegate();
    for (int i=0;i<5;i++) {
        ui->tableView->setColumnWidth(i,300);
        ui->tableView->setItemDelegateForColumn(i,read_only);
    }


}

people_search::~people_search()
{
    delete ui;
}

void people_search::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text().isEmpty()){

        people_model->setFilter(QString("inspectionPointNo='%1'").arg(p_prode->getInspectionNo()));
        people_model->select();

        return;
    }
    qDebug()<<ui->lineEdit->text();
    people_model->setFilter(QString("IMEI like '%%1%' AND inspectionPointNo='%2'").arg(ui->lineEdit->text()).arg(p_prode->getInspectionNo()));
    people_model->select();
}

void people_search::on_pushButton_clicked()
{
    QDateTime td1=ui->dateTimeEdit->dateTime();
    QDateTime td2=ui->dateTimeEdit_2->dateTime();
    if(td1.toSecsSinceEpoch()>td2.toSecsSinceEpoch()){
        QMessageBox::warning(this,tr("warning"),tr("time error!"),QMessageBox::Ok);
        return;
    }
    qint64 num_t1=td1.toSecsSinceEpoch();
    qint64 num_t2=td2.toSecsSinceEpoch();
    qDebug()<<num_t2;
    people_model->setFilter(QString("TimeStamp>=%1 AND TimeStamp<=%2 AND inspectionPointNo='%3'").arg(QString::number(num_t1)).arg(QString::number(num_t2)).arg(p_prode->getInspectionNo()));
    people_model->select();
}
