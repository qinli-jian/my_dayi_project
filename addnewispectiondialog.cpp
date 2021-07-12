#include "addnewispectiondialog.h"
#include "ui_addnewispectiondialog.h"
#include<QValidator>
#include<QSqlRecord>
addNewIspectionDialog::addNewIspectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewIspectionDialog)
{
    ui->setupUi(this);
    p=(QMainWindow*)parent;
    QDoubleValidator * dou = new QDoubleValidator(0,180,20,this);
    ui->lineEdit_LO->setValidator(dou);
    ui->lineEdit_LA->setValidator(dou);
}

addNewIspectionDialog::~addNewIspectionDialog()
{
    delete ui;
}

void addNewIspectionDialog::on_pushButton_clicked()
{
//    QStringList str;
//    str<<ui->lineEdit_ID->text()<<ui->lineEdit_LO->text()<<ui->lineEdit_LA->text();

    if(ui->lineEdit_ID->text().isEmpty()||ui->lineEdit_LO->text().isEmpty()||ui->lineEdit_LA->text().isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("There are unfilled contents!"),QMessageBox::Ok);
        return;
    }
    MainWindow*t_p=(MainWindow*)this->p;
    QSqlQuery q(t_p->get_inspectionData());
    QSqlRecord rec;
    q.exec("select * from inspection;");
    while (q.next()) {
        rec=q.record();
        int idcol = rec.indexOf("id");
        qDebug()<<q.value(idcol).toString();
        if(q.value(idcol).toString()==ui->lineEdit_ID->text()){
            QMessageBox::warning(this,tr("warning"),tr("The ID already exists!"),QMessageBox::Ok);
            return;
        }
    }


    QSqlTableModel *t_inspection = ((MainWindow*)p)->getInspectionModel();

   int rownum=t_inspection->rowCount();
   t_inspection->insertRow(rownum);
   t_inspection->setData(t_inspection->index(rownum,0),ui->lineEdit_ID->text());
   QDateTime currTime = QDateTime::currentDateTime();
   QString t = currTime.toString("yyyy-MM-dd h:m:s");
   t_inspection->setData(t_inspection->index(rownum,1),t);
   t_inspection->setData(t_inspection->index(rownum,2),ui->lineEdit_LO->text()+ui->comboBox_LO->currentText());
   t_inspection->setData(t_inspection->index(rownum,3),ui->lineEdit_LA->text()+ui->comboBox_LA->currentText());
   t_inspection->setData(t_inspection->index(rownum,4),QString::number(currTime.toSecsSinceEpoch()));
   t_inspection->submitAll();
    close();
}

void addNewIspectionDialog::on_pushButton_2_clicked()
{
    close();
}
