#include "datasearchui.h"
#include "ui_datasearchui.h"

DataSearchui::DataSearchui(MainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::DataSearchui)
{
    ui->setupUi(this);
    p_main=parent;
    car_database=p_main->get_carflowData();
    people_database=p_main->get_peopleflowData();
    video_database=QSqlDatabase::addDatabase("QSQLITE");
    video_database.setDatabaseName("../dayi_project_20210519/videoData.db");
    if(!video_database.open()){
        QMessageBox::warning(this,tr("warning"),tr("can not open video database!"),QMessageBox::Ok);
    }
    video_model=new QSqlTableModel(this,video_database);
    allcardata_model=new QSqlTableModel(this,car_database);
    allpeopledata_model=new QSqlTableModel(this,people_database);

    show_peopleflow();
    ui->pushButton->setEnabled(false);
    set_total();
}

DataSearchui::~DataSearchui()
{
    delete ui;
}

void DataSearchui::show_peopleflow()
{

    allpeopledata_model->setTable("passegerflow");
    ui->tableView->setModel(allpeopledata_model);
    allpeopledata_model->select();
    for (int i=0;i<5;i++) {
        ui->tableView->setColumnWidth(i,250);
        ui->tableView->setItemDelegateForColumn(i,&read_only);
    }

}

void DataSearchui::show_carflow()
{
    allcardata_model->setTable("traffic");
    ui->tableView->setModel(allcardata_model);
    allcardata_model->select();
    for (int i=0;i<5;i++) {
        ui->tableView->setColumnWidth(i,250);
        ui->tableView->setItemDelegateForColumn(i,&read_only);
    }

}

void DataSearchui::video_data()
{
      video_model->setTable("video");
      ui->tableView->setModel(video_model);
      video_model->select();
      for (int i=0;i<3;i++) {
          ui->tableView->setColumnWidth(i,400);
          ui->tableView->setItemDelegateForColumn(i,&read_only);
      }
}

void DataSearchui::set_total()
{
    if(ui->comboBox->currentIndex()==0){
        //人流
        QSqlQuery t(p_main->get_peopleflowData());
        t.exec("select count(*) from passegerflow;");
        t.next();
        ui->lineEdit_2->setText(QString::number(t.value(0).toInt()));
    }else if(ui->comboBox->currentIndex()==1){
        QSqlQuery t(p_main->get_carflowData());
        t.exec("select count(*) from traffic;");
        t.next();
        ui->lineEdit_2->setText(QString::number(t.value(0).toInt()));
    }else if(ui->comboBox->currentIndex()==2){
        QSqlQuery t(video_database);
        t.exec("select count(*) from video;");
        t.next();
        ui->lineEdit_2->setText(QString::number(t.value(0).toInt()));
    }
}

void DataSearchui::on_pushButton_clicked()
{
    if(ui->comboBox->currentIndex()==0){
        return;
    }
    double d1=ui->doubleSpinBox_1->value();
    double d2=ui->doubleSpinBox->value();
    if(d1>d2){
        QMessageBox::warning(this,tr("warning"),tr("speed error!"),QMessageBox::Ok);
        return;
    }

    allcardata_model->setFilter(QString("speed>=%1 AND speed<=%2").arg(QString::number(d1)).arg(QString::number(d2)));
    allcardata_model->select();

}

void DataSearchui::on_comboBox_currentIndexChanged(int index)
{
    ui->comboBox_2->setCurrentIndex(0);
    if(index==0){
        //人流数据
        ui->pushButton->setEnabled(false);
        show_peopleflow();
        ui->pushButton_name->setText("search by IMEI");
    }else if(index==1){
        ui->pushButton->setEnabled(true);
        show_carflow();
        ui->pushButton_name->setText("search by License plate");
    }else if(index==2){
        ui->pushButton->setEnabled(false);
        video_data();
        ui->pushButton_name->setText("search by equipment ID");
    }
    set_total();
}

void DataSearchui::on_pushButton_name_clicked()
{
    if(ui->comboBox->currentIndex()==0){
        //人流
        if(ui->lineEdit->text().isEmpty()){
            show_peopleflow();
        }else{
            allpeopledata_model->setFilter(QString("IMEI like '%%1%'").arg(ui->lineEdit->text()));
            allpeopledata_model->select();

        }
    }else if(ui->comboBox->currentIndex()==1){
        //车流
        if(ui->lineEdit->text().isEmpty()){
            show_carflow();
        }else{

            allcardata_model->setFilter(QString("licensePlate like '%%1%'").arg(ui->lineEdit->text()));
            allcardata_model->select();

        }
    }else if(ui->comboBox->currentIndex()==2){
        if(ui->lineEdit->text().isEmpty()){
            video_data();
        }else{
            video_model->setFilter(QString("equipmentID like '%%1%'").arg(ui->lineEdit->text()));
            video_model->select();
        }
    }
}

void DataSearchui::on_searchbytime_clicked()
{
    QDateTime td1=ui->dateTimeEdit->dateTime();
    QDateTime td2=ui->dateTimeEdit_2->dateTime();
    if(td1.toSecsSinceEpoch()>=td2.toSecsSinceEpoch()){
        QMessageBox::warning(this,tr("warning"),tr("time error!"),QMessageBox::Ok);
        return;
    }

    if(ui->comboBox->currentIndex()==0){
        //人流
        allpeopledata_model->setFilter(QString("TimeStamp>=%1 AND TimeStamp<=%2").arg(QString::number(td1.toSecsSinceEpoch())).arg(QString::number(td2.toSecsSinceEpoch())));
        allpeopledata_model->select();
    }else if(ui->comboBox->currentIndex()==1){
        //车流
        allcardata_model->setFilter(QString("TimeStamp>=%1 AND TimeStamp<=%2").arg(QString::number(td1.toSecsSinceEpoch())).arg(QString::number(td2.toSecsSinceEpoch())));
        allcardata_model->select();
    }else if(ui->comboBox->currentIndex()==2){
        video_model->setFilter(QString("time>='%1' AND time <= '%2'").arg(td1.toString("yyyy-MM-dd hh")).arg(td2.toString("yyyy-MM-dd hh")));
        video_model->select();
    }


}

void DataSearchui::on_comboBox_2_currentIndexChanged(int index)
{
    int kind_data=ui->comboBox->currentIndex();//0是人流
    if(kind_data==0){
        //人流
        if(ui->comboBox_2->currentIndex()==1){
            //升序
            allpeopledata_model->setSort(4,Qt::AscendingOrder);
            allpeopledata_model->select();
        }else if(ui->comboBox_2->currentIndex()==3){
            //时间降序
            allpeopledata_model->setSort(4,Qt::DescendingOrder);
            allpeopledata_model->select();
        }
    }else if(kind_data==1){
        //车流
        if(ui->comboBox_2->currentIndex()==1){
            //时间升序
            allcardata_model->setSort(4,Qt::AscendingOrder);
            allcardata_model->select();
        }else if(ui->comboBox_2->currentIndex()==2){
            allcardata_model->setSort(3,Qt::AscendingOrder);
            allcardata_model->select();
        }else if(ui->comboBox_2->currentIndex()==3){
            //时间降序
            allcardata_model->setSort(4,Qt::DescendingOrder);
            allcardata_model->select();
        }else if(ui->comboBox_2->currentIndex()==4){
            allcardata_model->setSort(3,Qt::DescendingOrder);
            allcardata_model->select();
        }
    }else if(kind_data==2){
        if(ui->comboBox_2->currentIndex()==1){
            //升序
            video_model->setSort(0,Qt::AscendingOrder);
            video_model->select();
        }else if(ui->comboBox_2->currentIndex()==3){
            video_model->setSort(0,Qt::DescendingOrder);
            video_model->select();
        }
    }
}

void DataSearchui::on_tableView_clicked(const QModelIndex &index)
{
    if(ui->comboBox->currentIndex()!=2)return;
    int row=index.row();
    QString path=video_model->data(video_model->index(row,2)).toString();
    QString title1 = video_model->data(video_model->index(row,1)).toString();
    QString title2 = video_model->data(video_model->index(row,0)).toString();

    showVideo *showvideo_facing=new showVideo(path,this);
    showvideo_facing->setWindowTitle(title2+"-"+title1+"-"+"Video");
    showvideo_facing->exec();
    delete showvideo_facing;
}
