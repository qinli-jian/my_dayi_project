#include "showequipmentdialog.h"
#include "ui_showequipmentdialog.h"

showEquipmentDialog::showEquipmentDialog(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::showEquipmentDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("equipment list");
    this->p=parent;
    equip_model = new QSqlTableModel(this,((MainWindow*)p)->get_equipmentData());
    equip_model->setTable("equipment");
    equip_model->select();
    equip_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(equip_model);
//    ui->tableView->setColumnWidth(0,150);
//    ui->tableView->setColumnWidth(1,150);
//    ui->tableView->setColumnWidth(2,150);
//    ui->tableView->setColumnWidth(3,150);
//    ui->tableView->setColumnWidth(4,150);
//    ui->tableView->setColumnWidth(5,150);
//    ui->tableView->setColumnWidth(6,150);
    for (int i=0;i<9;i++) {
        ui->tableView->setColumnWidth(i,200);
        ui->tableView->setItemDelegateForColumn(i,&read_only);
    }

    Refresh_total_tab();
}

void showEquipmentDialog::Refresh_total_tab()
{
    QSqlQuery t(p->get_equipmentData());
    t.exec("select count(*) from equipment;");
    t.next();
    ui->lineEdit_count->setText(QString::number(t.value(0).toInt()));
}

showEquipmentDialog::~showEquipmentDialog()
{
    delete ui;
}

void showEquipmentDialog::on_tableView_clicked(const QModelIndex &index)
{
    if(index.column()!=0)return;
    int row=index.row();
    QString equipment=equip_model->data(equip_model->index(row,0)).toString();
    QString kindname=equip_model->data(equip_model->index(row,1)).toString();
    QString installtime=equip_model->data(equip_model->index(row,2)).toString();
    QString LO=equip_model->data(equip_model->index(row,3)).toString();
    QString LA=equip_model->data(equip_model->index(row,4)).toString();
    QString inspectionPointNo=equip_model->data(equip_model->index(row,5)).toString();
    QString modelnum=equip_model->data(equip_model->index(row,6)).toString();
    int state=equip_model->data(equip_model->index(row,7)).toInt();
    if(kindname=="4G prode"){
        FourGProbe *four_p=new FourGProbe(equipment,installtime,LA,LO,modelnum,inspectionPointNo,state,p);
    }else if(kindname=="License plate"){
        LicensePlateMonitoring * lp=new LicensePlateMonitoring(equipment,installtime,LA,LO,modelnum,inspectionPointNo,state, p);
    }else if(kindname=="monitor"){
        VideoSurveillance *Video_p = new VideoSurveillance(equipment,installtime,LA,LO,modelnum,inspectionPointNo,state, p);
    }
}

void showEquipmentDialog::on_pushButton_5_clicked()
{
    ui->comboBox->setCurrentIndex(0);
    Refresh_total_tab();
    equip_model->submitAll();
}

void showEquipmentDialog::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text().isEmpty()){
        equip_model->setTable("equipment");
        equip_model->select();
        for (int i=0;i<9;i++) {
            ui->tableView->setColumnWidth(i,200);
            ui->tableView->setItemDelegateForColumn(i,&read_only);
        }

        return;
    }
    equip_model->setFilter(QString("id like '%%1%'").arg(ui->lineEdit->text()));
    equip_model->select();
}

void showEquipmentDialog::on_pushButton_clicked()
{
    QDateTime td1=ui->dateTimeEdit->dateTime();
    QDateTime td2=ui->dateTimeEdit_2->dateTime();
    qint64 t1=td1.toSecsSinceEpoch();
    qint64 t2=td2.toSecsSinceEpoch();
    if(t1>t2){
        QMessageBox::warning(this,tr("warning"),tr("time error!"),QMessageBox::Ok);
        return;
    }
    equip_model->setFilter(QString("TimeStamp>=%1 AND TimeStamp<=%2").arg(QString::number(t1)).arg(QString::number(t2)));
    equip_model->select();
}

void showEquipmentDialog::on_pushButton_4_clicked()
{
    QModelIndex index=ui->tableView->currentIndex();
    int row=index.row();
    if(row==-1){
        return;
    }
    equip_model->removeRow(row);
        int ok=QMessageBox::warning(this,tr("delete this row!"),tr("Are you sure you want to delete this line?")
                                    ,QMessageBox::Yes,QMessageBox::No);
        if(ok==QMessageBox::No){
            equip_model->revertAll();
        }else{
        equip_model->submitAll();
    }
     this->Refresh_total_tab();
}

void showEquipmentDialog::on_comboBox_currentIndexChanged(int index)
{
    if(index==1){
        //升序
        equip_model->setSort(8,Qt::AscendingOrder);
        equip_model->select();
    }else if(index==2){
        equip_model->setSort(8,Qt::DescendingOrder);
        equip_model->select();
    }
}
