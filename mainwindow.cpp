#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QList>
#include<QMetaType>
#include"readonlyClass.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    equipment_Model=nullptr;
    inspectiondataModel=nullptr;
    allf=new QFont;
    allf->setFamily("Calibri");
    allf->setPixelSize(20);
    allf->setPointSize(30);
    allf->setBold(true);

    ui->label_5->setFont(*allf);

    road = new Road;
//    ui->tableWidget_2->setColumnCount(3);
//    ui->tableWidget_2->setRowCount(1000);

//    ui->tableWidget_2->setColumnWidth(0,200);
//    ui->tableWidget_2->setColumnWidth(1,200);
//     ui->tableWidget_2->setColumnWidth(2,290);
//    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"Inspection point number"<<"Latitude and longitude"<<"Installation time");

//    inspectiondata = new QSqlTableModel(this);
//    inspectiondata->setTable("inspectionpoint");
//    inspectiondata->select();

//    inspectiondata->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //ui->tableView->setModel(inspectiondata);
    //ConnectDataBase();

    QDoubleValidator * dou = new QDoubleValidator(0,180,20,this);
    ui->lineEdit_lo->setValidator(dou);
    ui->lineEdit_la->setValidator(dou);

    qDebug()<<QSqlDatabase::drivers();

    ConnectDataBase();
    qDebug()<<"47";

//    QSqlQuery q(inspectionPointData);

//    if(!q.exec("select * from inspectionpoint;")){
//        qDebug()<<"no";
//    }


//    QSqlQueryModel*model = new QSqlQueryModel(this);
//    model->setQuery(q);

//    model->setHeaderData(0,Qt::Horizontal,tr("IMEI"));
//    model->setHeaderData(1,Qt::Horizontal,tr("station"));
//    model->setHeaderData(2,Qt::Horizontal,tr("num"));
//    model->setHeaderData(3,Qt::Horizontal,tr("time"));

    inspectiondataModel = new QSqlTableModel(this,inspectionPointData);
    inspectiondataModel->setTable("inspection");
    inspectiondataModel->select();
    inspectiondataModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(inspectiondataModel);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,250);
    ui->tableView->setColumnWidth(2,150);
    ui->tableView->setColumnWidth(3,150);
    ReadOnlyDelegate *read_only=new ReadOnlyDelegate();
    for(int i=0;i<5;i++){
        ui->tableView->setItemDelegateForColumn(i,read_only);
    }

//    QSqlQuery t(trafficData);
//    t.exec("select * from traffic;");
//    QDateTime ttime;
//    while (t.next()) {
//        ttime=QDateTime::fromString(t.record().value(1).toString(),"yyyy-M-dd h:mm");
//        if(ttime.toSecsSinceEpoch()<=0){
//             ttime=QDateTime::fromString(t.record().value(1).toString(),"yyyy-MM-dd h:mm");
//        }
//        if(ttime.toSecsSinceEpoch()<=0){
//             ttime=QDateTime::fromString(t.record().value(1).toString(),"yyyy-M-dd hh:mm");
//        }
//        if(ttime.toSecsSinceEpoch()<=0){
//             ttime=QDateTime::fromString(t.record().value(1).toString(),"yyyy-MM-dd hh:mm");
//        }

//        //t.exec(QString("update traffic set TimeStamp=%1 where licensePlate='%2';").arg(ttime.toSecsSinceEpoch()).arg(t.record().value(0).toString()));
//        //t.exec("select * from traffic;");
//        t.record().setValue(4,QString::number(ttime.toSecsSinceEpoch()));
//        qDebug()<<ttime.toSecsSinceEpoch();
//        qDebug()<<t.record().value(5).toString();
//    }

//    RandomData r(this);
//    r.random_peopleData(get_peopleflowData(),1,"nihao","shebei");
//    r.random_carData(get_carflowData(),1,"nihao");


}

MainWindow::~MainWindow()
{
    delete allf;
    delete ui;
}






void MainWindow::on_pushButton_clicked()
{

    addNewIspectionDialog add_dialog(this);
    add_dialog.exec();

}


void MainWindow::on_pushButton_4_clicked()
{
    RoadInformationWidget*roadInfo = new RoadInformationWidget(this);

    roadInfo->exec();
}

void MainWindow::on_deletepushButton_clicked()
{
    //connect(this,&MainWindow::seletedRow,road,&Road::deleteMonitoringPoint);
//    if(row>=0){
//        road->deleteMonitoringPoint(row);

//        MonitoringPoint::acountMonitoring--;
//    }
//    row=-1;
    int row = ui->tableView->currentIndex().row();
    QString inspectionId=inspectiondataModel->data(inspectiondataModel->index(row,0)).toString();
    qDebug()<<row;
    if(row==-1){
        return;
    }
    inspectiondataModel->removeRow(row);
    int ok=QMessageBox::warning(this,tr("delete this row!"),tr("Are you sure you want to delete this line?")
                                ,QMessageBox::Yes,QMessageBox::No);
    if(ok==QMessageBox::No){
        inspectiondataModel->revertAll();
    }else{
        //equipment也要删除
        QSqlQuery temp(equipmentData);
        temp.exec(QString("delete from equipment where inspectionPointNo = '%1';").arg(inspectionId));
        equipment_Model->submitAll();
        inspectiondataModel->submitAll();
    }
}


void MainWindow::on_MainWindow_destroyed()
{

    inspectiondataModel->submitAll();
    equipment_Model->submitAll();
}

void MainWindow::on_pushButton_3_clicked()
{
    DataSearchui *datas=new DataSearchui(this);
    datas->setWindowModality(Qt::ApplicationModal);
    datas->show();

}


bool MainWindow::ConnectDataBase(){
    QString pathhead="../dayi_project_20210519/";
//    QFile file("../dayi_project_20210519/p.csv"); //打开csv文件

//    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
//        QMessageBox::critical(nullptr,"Cannot open inspectionpoint database11!","Unable to establish a database connection.",QMessageBox::Cancel);
//        return false;
//    }
//-------------------------------------------------------------------****************************--------------------------------------------------------------------------
//    inspectionPointData = QSqlDatabase::addDatabase("QSQLITE","inspectionpoint");
//    inspectionPointData.setDatabaseName("inspectionpointdata.db");
//    if(!inspectionPointData.open()){
//        QMessageBox::critical(nullptr,"Cannot open inspectionpoint database22!","Unable to establish a database connection.",QMessageBox::Cancel);
//        return false;
//    }

    //QSqlQuery q1(inspectionPointData);

    //QSqlQuery sql_query(inspectionPointData);

//    if(!q1.exec("create table inspectionpoint(IMEI varchar(30) primary key,time varchar(30),station varchar(20),num varchar(20));")){
//        qDebug()<<"create error!!!";
//    }
//    QStringList list;
//    list.clear();
//    QTextStream in(&file);
//    //int acount=0;
//    QString t;
//    t= in.readLine();
//    t= in.readLine();
//    while (!in.atEnd()) {
//        QString fileLLine = in.readLine();
//        list = fileLLine.split(",",QString::SkipEmptyParts);
//        qDebug()<<list.at(0);

//        if(!q1.exec("insert into inspectionpoint(IMEI,time,station,num) values('"+QString(list.at(3))+"','"+QString(list.at(0)) +"','"+QString(list.at(1))+"','"+QString(list.at(2))+"');")){
//                qDebug()<<"insert error!!!";
//    }

//}
//begin here
    roadData = QSqlDatabase::addDatabase("QSQLITE","road");
    roadData.setDatabaseName(pathhead+"road.db");
    if(!roadData.open()){
        QMessageBox::critical(nullptr,"Cannot open road database!","Unable to establish a database connection.",QMessageBox::Cancel);
        return false;
    }
//    QSqlQuery t0;
//    qDebug()<<t0.exec(QString("select count(*) from sqlite_master where type = 'table' and name = '%1';;").arg("road"));

//    if(t0.exec(QString("select count(*) from sqlite_master where type = 'table' and name = '%1';;").arg("road"))==0){
//    QSqlQuery q_road(roadData);
//    if(!q_road.exec("create table road(StartingLongitude varchar(10),StartingLatitude varchar(10),EndLongitude varchar(10),EndLatitude varchar(10));")){
//        QMessageBox::critical(nullptr,"Cannot create road database!","Unable to establish a database connection.",QMessageBox::Cancel);
//        return false;
//    }
//    q_road.exec("insert into road(StartingLongitude,StartingLatitude,EndLongitude,EndLatitude) values('123.4565482N','123.8945234E','124.9694524N','124.0394548E');");
//}
    //----*****--------------------------------------
    inspectionPointData=QSqlDatabase::addDatabase("QSQLITE","inspectionconnect");
    inspectionPointData.setDatabaseName(pathhead+"inspectionPoint.db");
    if(!inspectionPointData.open()){
        QMessageBox::critical(nullptr,"Cannot open inspection point database!","Unable to establish a database connection.",QMessageBox::Cancel);
        return false;
    }
//    QSqlQuery q_inspection(inspectionPointData);
//    q_inspection.exec("create table inspection( id varchar(20) primary key,installationTime varchar(30),Longitude varchar(10), Latitude varchar(10));");
//    QSqlQuery t;
//    qDebug()<<"111"<<t.exec(QString("select count(*) from sqlite_master where type = 'table' and name = '%1';").arg("inspection"));
//    bool isT=t.exec(QString("select count(*) from sqlite_master where type = 'table' and name = '%1';").arg("inspection"));
//    qDebug()<<isT;
//    if(t.next()){
//    if(t.value(0).toInt()==0){
//    QSqlQuery q_inspection(inspectionPointData);
//    if(!q_inspection.exec("create table inspection( id varchar(20) primary key,installationTime varchar(30),Longitude varchar(10), Latitude varchar(10));")){
//        QMessageBox::critical(nullptr,"Cannot create inspection database!","Unable to establish a database connection.",QMessageBox::Cancel);
//        return false;
//    }
//}else{
//        qDebug()<<"e";
//    }
//    }
//    qDebug()<<"inspection";
    //--------------------------------------

    equipmentData = QSqlDatabase::addDatabase("QSQLITE","equipment");
    equipmentData.setDatabaseName(pathhead+"equipment.db");
    if(!equipmentData.open()){
        QMessageBox::critical(nullptr,"Cannot open equipment database!","Unable to establish a database connection.",QMessageBox::Cancel);
        return false;
    }
//    QSqlQuery t1;t1.exec(QString("select count(*) from sqlite_master where type = 'table' and name = '%1';;").arg("equipment"));
//    if(t1.next()){
//    if(t1.value(0).toInt()==0){
//    QSqlQuery q_equipment(equipmentData);
//    if(!q_equipment.exec("create table equipment(  id varchar(20) primary key,kindName varvhar(15),installationTime varchar(30)"
//                          ",Longitude varchar(10), Latitude varchar(10),"
//                          "inspectionPointNo varchar(20),modelNum varchar(10));")){
//        QMessageBox::critical(nullptr,"Cannot create equipment database!","Unable to establish a database connection.",QMessageBox::Cancel);
//        return false;
//    }
//    }
//    }
    qDebug()<<"245";
    /*
    if(!q_equipment.exec("create table licensePlateRecognition(  id varchar(20) primary key,installationTime varchar(30)"
                          ",Longitude varchar(10), Latitude varchar(10),"
                          "inspectionPointNo varchar(20),modelNum varchar(10));")){
        QMessageBox::critical(nullptr,"Cannot create equipment database!","Unable to establish a database connection.",QMessageBox::Cancel);
        return false;
    }
    if(!q_equipment.exec("create table Monitor(  id varchar(20) primary key,installationTime varchar(30)"
                          ",Longitude varchar(10), Latitude varchar(10),"
                          "inspectionPointNo varchar(20),modelNum varchar(10));")){
        QMessageBox::critical(nullptr,"Cannot create equipment database!","Unable to establish a database connection.",QMessageBox::Cancel);
        return false;
    }
    */

    //--------------------------------------------------

    passegerflowData = QSqlDatabase::addDatabase("QSQLITE","passeger");
    passegerflowData.setDatabaseName(pathhead+"passegerflow.db");
    if(!passegerflowData.open()){
        QMessageBox::critical(nullptr,"Cannot open passeger flow database1!","Unable to establish a database connection.",QMessageBox::Cancel);
        return false;
    }
//    QSqlQuery t2;t2.exec(QString("select count(*) from sqlite_master where type = 'table' and name = '%1';").arg("passegerflow"));
//    qDebug()<<"277";
//    qDebug()<<t2.value(0).toInt();
//    if(t2.value(0).toInt()==0){
//   QSqlQuery q_passegerflow(passegerflowData);
//   QDateTime tdt;
//    if(!q_passegerflow.exec("create table passegerflow(  IMEI varchar(30) ,time varchar(30),"
//                          "inspectionPointNo varchar(20),equipmentid varchar(10),TimeStamp varchar(30));")){
//        QMessageBox::critical(nullptr,"Cannot create passeger flow database!","Unable to establish a database connection.",QMessageBox::Cancel);
//        return false;
//    }
//    QStringList peopleflow_path;
//    peopleflow_path<<pathhead+"p01.csv"<<pathhead+"p02.csv"<<pathhead+"p03.csv";
//    for (int i=0;i<3;i++) {
//        QFile p_f(peopleflow_path.at(i));
//        if(!p_f.open(QIODevice::ReadOnly|QIODevice::Text)){
//                QMessageBox::critical(nullptr,"Cannot open passeger flow database11!","Unable to establish a database connection.",QMessageBox::Cancel);
//                return false;
//            }
//        QString t;
//        t=p_f.readLine();
//        t=p_f.readLine();
//        QStringList list_p,ans_time,imei_list;
//        while (!p_f.atEnd()) {
//            t=p_f.readLine();
//            list_p = t.split(",",QString::SkipEmptyParts);
//            ans_time=list_p.at(0).split("T");
//            //qDebug()<<ans_time;
//            tdt=QDateTime::fromString(QString(ans_time.at(0)+" "+ans_time.at(1)),"yyyy-MM-dd hh:mm:ss");
//            qDebug()<<QString(ans_time.at(0)+" "+ans_time.at(1));
//            imei_list=list_p.at(3).split("\n");
//            //qDebug()<<imei_list;
//            q_passegerflow.exec(QString("insert into passegerflow(IMEI,time,inspectionPointNo,equipmentid,TimeStamp)"
//                                        " values('%1','%2','%3','%4','%5');").arg(imei_list.at(0)).arg(list_p.at(0)).arg(list_p.at(1)).arg(list_p.at(2)).arg(QString::number(tdt.toSecsSinceEpoch())));
//        }
//    }
//}

//---------------------------------------------
    trafficData = QSqlDatabase::addDatabase("QSQLITE","traffic");
    trafficData.setDatabaseName(pathhead+"traffic.db");
    if(!trafficData.open()){
        QMessageBox::critical(nullptr,"Cannot open traffic database!","Unable to establish a database connection.",QMessageBox::Cancel);
        return false;
    }

//    QSqlQuery t3;t3.exec(QString("select count(*) from sqlite_master where type = 'table' and name = '%1';;").arg("traffic"));

//    qDebug()<<"t3";
//    if(t3.record().value(0)==0){
//    QSqlQuery q_traffic(trafficData);
//    if(!q_traffic.exec("create table traffic( licensePlate varchar(30),time varchar(30),"
//                       "inspectionPointNo varchar(20),speed varchar(10),TimeStamp varchar(30));")){
//        QMessageBox::critical(nullptr,"Cannot create traffic database!","Unable to establish a database connection.",QMessageBox::Cancel);
//        return false;
//    }
//    QStringList straffic_path;
//    straffic_path<<pathhead+"traffic01.csv"<<pathhead+"traffic02.csv"<<pathhead+"traffic03.csv";
//    QDateTime tdt;
//    for (int i=0;i<3;i++) {
//        QFile tra_f(straffic_path.at(i));
//        qDebug()<<straffic_path.at(i);
//        if(!tra_f.open(QIODevice::ReadOnly|QIODevice::Text)){
//                QMessageBox::critical(nullptr,"Cannot open traffic flow database11!","Unable to establish a database connection.",QMessageBox::Cancel);
//                return false;
//            }
//        QString t;
//        t=tra_f.readLine();
//        t=tra_f.readLine();
//        QStringList list_p,ans;int c=0;

//        while (!tra_f.atEnd()) {
//            t=tra_f.readLine();
//            //qDebug()<<t;
//            list_p = t.split(",",QString::SkipEmptyParts);
//            tdt=QDateTime::fromString(list_p.at(0),"yyyy-M-dd h:mm");
//            if(tdt.toSecsSinceEpoch()<=0){
//                tdt=QDateTime::fromString(list_p.at(0),"yyyy-MM-dd h:mm");
//            }
//            if(tdt.toSecsSinceEpoch()<=0){
//                tdt=QDateTime::fromString(list_p.at(0),"yyyy-M-dd hh:mm");
//            }
//            if(tdt.toSecsSinceEpoch()<=0){
//                tdt=QDateTime::fromString(list_p.at(0),"yyyy-MM-dd hh:mm");
//            }
//            ans=list_p.at(1).split(" ");
//            //qDebug()<<ans.join("");
//           c++;
//            q_traffic.exec(QString("insert into traffic(licensePlate,time,inspectionPointNo,speed,TimeStamp)"
//                                        " values('%1','%2','%3','%4','%5');").arg(list_p.at(3)).arg(list_p.at(0)).arg(ans.join("")).arg(QString::number(list_p.at(2).toDouble()/100)).arg(QString::number(tdt.toSecsSinceEpoch())));
//        }
//        qDebug()<<c;
//        c=0;
//    }
//}

    return true;
}

void MainWindow::on_pushButton_submit_clicked()
{
    inspectiondataModel->database().transaction();//开始事务操作
    if(inspectiondataModel->submitAll()){
        if(inspectiondataModel->database().commit()){
            QMessageBox::information(this,tr("information"),tr("Success!"));
        }else {
            inspectiondataModel->database().rollback();//回滚
            QMessageBox::warning(this,tr("warning"),tr("ERROR"),QMessageBox::Ok);
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    inspectiondataModel->revertAll();
}

void MainWindow::on_SearchpushButton_clicked()
{
    QString data=ui->lineEdit->text();
    if(ui->lineEdit->text().isEmpty()){
        inspectiondataModel->setTable("inspection");
        inspectiondataModel->select();
        ui->tableView->setColumnWidth(0,200);
        ui->tableView->setColumnWidth(1,250);
        ui->tableView->setColumnWidth(2,150);
        ui->tableView->setColumnWidth(3,150);
        return;
    }
    inspectiondataModel->setFilter(QString("id like '%%1%'").arg(data));
   inspectiondataModel->select();
}

QSqlTableModel* MainWindow::getInspectionModel(){
    return inspectiondataModel;
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    this->index=index;
    qDebug()<<index.column();
    qDebug()<<inspectiondataModel->data(inspectiondataModel->index(index.row(),0)).toString();
    QString id = inspectiondataModel->data(inspectiondataModel->index(index.row(),0)).toString();
    QString itime = inspectiondataModel->data(inspectiondataModel->index(index.row(),1)).toString();
    QString lo = inspectiondataModel->data(inspectiondataModel->index(index.row(),2)).toString();
    QString la = inspectiondataModel->data(inspectiondataModel->index(index.row(),3)).toString();
    int comboxlo_index;
    int comboxla_index;
    if(lo[lo.size()-1]=="E"){
        comboxlo_index=0;
    }else{
        comboxlo_index=1;
    }
    lo=lo.left(lo.size()-1);
    if(la[la.size()-1]=="N"){
        comboxla_index=0;
    }else{
        comboxla_index=1;
    }
    la=la.left(la.size()-1);
    p_inspection=new MonitoringPoint(id,la,lo,itime);
    ui->lineEdit_id->setText(p_inspection->getNum());
    ui->lineEdit_la->setText(p_inspection->getLa());
    ui->comboBox_la->setCurrentIndex(comboxla_index);
    ui->lineEdit_lo->setText(p_inspection->getLo());
    ui->comboBox_lo->setCurrentIndex(comboxlo_index);
    ui->label_itime->setText(p_inspection->get_itime());
    QSqlQuery q_four(equipmentData);
    q_four.exec(QString("select * from equipment;"));
    equipment_Model=new QSqlTableModel(this,equipmentData);
    equipment_Model->setTable("equipment");
    equipment_Model->select();
    equipment_Model->setFilter(tr("inspectionPointNo='%1'").arg(inspectiondataModel->data(inspectiondataModel->index(index.row(),0)).toString()));
    equipment_Model->select();
    equipment_Model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_2->setModel(equipment_Model);
    ReadOnlyDelegate* readOnly=new ReadOnlyDelegate();
    ui->tableView_2->setItemDelegateForColumn(0,readOnly);
    ui->tableView_2->setItemDelegateForColumn(1,readOnly);
    ui->tableView_2->setItemDelegateForColumn(2,readOnly);
    ui->tableView_2->setItemDelegateForColumn(3,readOnly);
    ui->tableView_2->setItemDelegateForColumn(4,readOnly);
    ui->tableView_2->setItemDelegateForColumn(5,readOnly);
    ui->tableView_2->setItemDelegateForColumn(6,readOnly);
    ui->tableView_2->setColumnWidth(0,150);
    ui->tableView_2->setColumnWidth(1,150);
    ui->tableView_2->setColumnWidth(2,200);
    ui->tableView_2->setColumnWidth(3,150);
    ui->tableView_2->setColumnWidth(4,150);
    ui->tableView_2->setColumnWidth(5,150);
    ui->tableView_2->setColumnWidth(6,150);

//    equipment_Model->setData(equipment_Model->index(0,0),"01");
//    equipment_Model->submitAll();
    qDebug()<<"go";

}

void MainWindow::on_AddEquipmentpushButton_clicked()
{
    QModelIndex cur=ui->tableView->currentIndex();
    if(!cur.isValid()){
       qDebug()<<"kong";
        return;
    }
    QString inspectionId=inspectiondataModel->data(inspectiondataModel->index(cur.row(),0)).toString();
    QString LO = inspectiondataModel->data(inspectiondataModel->index(cur.row(),2)).toString();
    QString LA = inspectiondataModel->data(inspectiondataModel->index(cur.row(),3)).toString();

    qDebug()<<inspectionId;
    //下面就要开始增加设备了！
    addNewEquipmentDialog new_equipment(LO,LA,inspectionId,this);
    new_equipment.setWindowTitle("Add equipment");
    new_equipment.exec();

}

QSqlDatabase& MainWindow::get_inspectionData(){
    return inspectionPointData;
}

QSqlDatabase& MainWindow::get_equipmentData(){
    return this->equipmentData;
}

QSqlTableModel* MainWindow::get_equipmentModel(){
    return (this->equipment_Model);
}

QSqlDatabase& MainWindow::get_peopleflowData()
{
    return passegerflowData;
}

QSqlDatabase &MainWindow::get_carflowData()
{
    return trafficData;
}

MonitoringPoint *MainWindow::get_inspection()
{
    return p_inspection;
}

QModelIndex MainWindow::get_quip_index()
{
    return equipment_intdex;
}

void MainWindow::changeData(int f)
{
    int equipmentCount=equipment_Model->rowCount();
    for (int i=0;i<equipmentCount;i++) {
        qDebug()<<"change data!!!";
        equipment_Model->setData(equipment_Model->index(i,3),ui->lineEdit_lo->text()+ui->comboBox_lo->currentText());
        equipment_Model->setData(equipment_Model->index(i,4),ui->lineEdit_la->text()+ui->comboBox_la->currentText());
        if(!f){
        equipment_Model->setData(equipment_Model->index(i,5),ui->lineEdit_id->text());
        }
    }
    equipment_Model->submitAll();
    ui->tableView_2->setModel(equipment_Model);
}

void MainWindow::on_DeleteEquipmentpushButton_clicked()
{
        QModelIndex index = ui->tableView_2->currentIndex();
        int row=index.row();
        if(row==-1){
            return;
        }
        equipment_Model->removeRow(row);
        int ok=QMessageBox::warning(this,tr("delete this row!"),tr("Are you sure you want to delete this line?")
                                    ,QMessageBox::Yes,QMessageBox::No);
        if(ok==QMessageBox::No){
            equipment_Model->revertAll();
        }else{
            equipment_Model->submitAll();
            inspectiondataModel->submitAll();
        }
}

void MainWindow::on_pushButton_6_clicked()
{
    showEquipmentDialog *showEquipment=new showEquipmentDialog(this);
    showEquipment->show();
}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{

    equipment_intdex=ui->tableView_2->currentIndex();
    int row=index.row();
    if(row==-1||index.column()!=0)return;
    qDebug()<<index.row();

    QString equipment=equipment_Model->data(equipment_Model->index(row,0)).toString();
    QString kindname=equipment_Model->data(equipment_Model->index(row,1)).toString();
    QString installtime=equipment_Model->data(equipment_Model->index(row,2)).toString();
    QString LO=equipment_Model->data(equipment_Model->index(row,3)).toString();
    QString LA=equipment_Model->data(equipment_Model->index(row,4)).toString();
    QString inspectionPointNo=equipment_Model->data(equipment_Model->index(row,5)).toString();
    QString modelnum=equipment_Model->data(equipment_Model->index(row,6)).toString();
    int state=equipment_Model->data(equipment_Model->index(row,7)).toInt();
    qDebug()<<equipment_Model->data(equipment_Model->index(row,0)).toString();
    if(kindname=="4G prode"){
        FourGProbe *four_p=new FourGProbe(equipment,installtime,LA,LO,modelnum,inspectionPointNo,state,this);
        delete four_p;
    }else if(kindname=="License plate"){
        LicensePlateMonitoring * lp=new LicensePlateMonitoring(equipment,installtime,LA,LO,modelnum,inspectionPointNo,state, this);
        delete lp;
    }else if(kindname=="monitor"){
        VideoSurveillance *Video_p = new VideoSurveillance(equipment,installtime,LA,LO,modelnum,inspectionPointNo,state, this);
        delete Video_p;
    }
}



void MainWindow::on_lineEdit_id_editingFinished()
{

//    int row=index.row();
//    if(row==-1||p_inspection->getNum()==ui->lineEdit_id->text()){
//        qDebug()<<"not change!";
//        return;
//    }

//    QSqlQuery q_inspe(inspectionPointData);
//    q_inspe.exec("select*from inspection;");
//    QSqlRecord rec;
//    while (q_inspe.next()) {
//        rec=q_inspe.record();
//        int idcol = rec.indexOf("id");
//        qDebug()<<rec.value(idcol).toString();
//        if(rec.value(idcol).toString()==ui->lineEdit_id->text()){
//            QMessageBox::warning(this,tr("warning"),tr("The ID already exists!"),QMessageBox::Ok);
//            return;
//        }
//    }
//    p_inspection->setNum(ui->lineEdit_id->text());
//    changeData();
//    inspectiondataModel->setData(inspectiondataModel->index(row,0),ui->lineEdit_id->text());
//    inspectiondataModel->submitAll();
//    ui->tableView->setCurrentIndex(index);
}

void MainWindow::on_lineEdit_lo_editingFinished()
{

//    qDebug()<<index.row();
//    if(index.row()==-1||p_inspection->getLo()==ui->lineEdit_lo->text()){
//        qDebug()<<"not change!";return;
//    }

//    changeData();
//    int row=index.row();
//    p_inspection->setLo(ui->lineEdit_lo->text());
//    inspectiondataModel->setData(inspectiondataModel->index(row,2),ui->lineEdit_lo->text());
//    inspectiondataModel->submitAll();


}

void MainWindow::on_lineEdit_la_editingFinished()
{

//    if(index.row()==-1||p_inspection->getLa()==ui->lineEdit_la->text()){
//        qDebug()<<"not change!";
//        return;
//    }
//    changeData();
//    int row=index.row();
//    p_inspection->setLa(ui->lineEdit_la->text());
//    inspectiondataModel->setData(inspectiondataModel->index(row,3),ui->lineEdit_la->text());
//    inspectiondataModel->submitAll();

}

void MainWindow::on_pushButton_7_clicked()
{

        int row=index.row();
        if(row==-1||p_inspection->getNum()==ui->lineEdit_id->text()){
            qDebug()<<"not change!";

        }
        int f=0;
        QSqlQuery q_inspe(inspectionPointData);
        q_inspe.exec("select*from inspection;");
        QSqlRecord rec;
        while (q_inspe.next()) {
            rec=q_inspe.record();
            int idcol = rec.indexOf("id");
            qDebug()<<rec.value(idcol).toString();
            if(rec.value(idcol).toString()==ui->lineEdit_id->text()){
                QMessageBox::warning(this,tr("warning"),tr("The ID already exists!"),QMessageBox::Ok);
                f=1;
                ui->lineEdit_id->setText(p_inspection->getNum());
                break;
            }
        }
        if(!f){
        p_inspection->setNum(ui->lineEdit_id->text());
        inspectiondataModel->setData(inspectiondataModel->index(row,0),ui->lineEdit_id->text());
        }
        changeData(f);
        inspectiondataModel->setData(inspectiondataModel->index(row,3),ui->lineEdit_la->text()+ui->comboBox_la->currentText());
        inspectiondataModel->setData(inspectiondataModel->index(row,2),ui->lineEdit_lo->text()+ui->comboBox_lo->currentText());
        inspectiondataModel->submitAll();
        ui->tableView->setCurrentIndex(index);
}

void MainWindow::on_pushButton_8_clicked()
{
    QDateTime td1=ui->dateTimeEdit->dateTime();
    QDateTime td2=ui->dateTimeEdit_2->dateTime();
    qint64 t1=td1.toSecsSinceEpoch();
    qint64 t2=td2.toSecsSinceEpoch();
    if(t1>t2){
        QMessageBox::warning(this,tr("warning"),tr("time error!"),QMessageBox::Ok);
        return;
    }
    inspectiondataModel->setFilter(QString("TimeStamp>=%1 AND TimeStamp<=%2").arg(QString::number(t1)).arg(QString::number(t2)));
        inspectiondataModel->select();

}

void MainWindow::on_pushButton_5_clicked()
{

    if(ui->pushButton_5->text()=="ascending order by time"){
    inspectiondataModel->setSort(4,Qt::AscendingOrder);
    ui->pushButton_5->setText("descending order by time");
    }else if(ui->pushButton_5->text()=="descending order by time"){
    inspectiondataModel->setSort(4,Qt::DescendingOrder);
    ui->pushButton_5->setText("ascending order by time");
    }
    inspectiondataModel->select();
}
