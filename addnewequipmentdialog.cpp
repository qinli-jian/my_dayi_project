#include "addnewequipmentdialog.h"
#include "ui_addnewequipmentdialog.h"
#include<QDebug>

addNewEquipmentDialog::addNewEquipmentDialog(QString lo,QString la,QString inspectionID,QMainWindow *parent) :
    QDialog(parent),
    ui(new Ui::addNewEquipmentDialog)
{
    ui->setupUi(this);
    this->p=parent;
    curInspectionID=inspectionID;
    this->LO=lo;
    LA=la;

}

addNewEquipmentDialog::~addNewEquipmentDialog()
{
    delete ui;
}

void addNewEquipmentDialog::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty()||ui->lineEdit_4->text().isEmpty()){
        qDebug()<<"add kong";
        QMessageBox::warning(this,tr("warning"),tr("Not complete!"),QMessageBox::Ok);
        return;
    }

    MainWindow *p_temp=(MainWindow*)this->p;
    QSqlTableModel* model_t=p_temp->get_equipmentModel();
    QSqlDatabase& equipmentdata=p_temp->get_equipmentData();
    QSqlQuery q_equip(equipmentdata);
    if(!q_equip.exec("select * from equipment;")){
        qDebug()<<"select database table fail!";
    }

//    QSqlDatabase& inspectiondata=p_temp->get_inspectionData();
//    QSqlQuery q_inspection(inspectiondata);
//    QSqlRecord rec1;
//    while (!q_inspection.next()) {
//        rec1=q_inspection.record();
//        int numcol1=rec1.indexOf("id");
//        if(q_inspection.value(numcol1).toString()==this->curInspectionID&&ui->comboBox_3->currentText()==)
//    }

    qDebug()<<this->curInspectionID;
    QSqlRecord re;
    while (q_equip.next()) {
        re=q_equip.record();
        int numcol = re.indexOf("id");
        int numcol2 = re.indexOf("kindName");
        int numcol3 = re.indexOf("inspectionPointNo");
        qDebug()<<q_equip.value(numcol3).toString();
        if(q_equip.value(numcol).toString()==ui->lineEdit->text()||(q_equip.value(numcol3).toString()==this->curInspectionID&&q_equip.value(numcol2).toString()==ui->comboBox_3->currentText())){
            qDebug()<<"had same!";
            QMessageBox::warning(this,tr("warning"),tr("There is a device"
                                                       " with the same number or it has been "
                                                       "installed in the detection point!"),QMessageBox::Ok);
            return;
        }
    }
    QDateTime currTime = QDateTime::currentDateTime();
    QString t = currTime.toString("yyyy-MM-dd h:m:s");
    int rownum = model_t->rowCount();
    model_t->insertRow(rownum);
    model_t->setData(model_t->index(rownum,0),ui->lineEdit->text());
    model_t->setData(model_t->index(rownum,1),ui->comboBox_3->currentText());
    model_t->setData(model_t->index(rownum,2),t);
    model_t->setData(model_t->index(rownum,3),LO);
    model_t->setData(model_t->index(rownum,4),LA);
    model_t->setData(model_t->index(rownum,5),this->curInspectionID);
    model_t->setData(model_t->index(rownum,6),ui->lineEdit_4->text());
    model_t->setData(model_t->index(rownum,7),QString::number(1-ui->comboBox->currentIndex()));
    model_t->setData(model_t->index(rownum,8),QString::number(currTime.toSecsSinceEpoch()));
    model_t->submitAll();
    close();

}

void addNewEquipmentDialog::on_pushButton_2_clicked()
{
    close();
}
