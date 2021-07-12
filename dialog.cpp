#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
Dialog::Dialog(VideoSurveillance *parent,QMainWindow*p) :
    QDialog(p),
    ui(new Ui::Dialog)
{
        ui->setupUi(this);
        player = new QMediaPlayer;
        connectDataBase();
        this->p=(MainWindow*)p;
        video_object=parent;

        QDateTime currtime=ui->dateTimeEdit->dateTime();
        QDate d1(2021,04,25);
        QTime t1(16,00);
        QDateTime qdt(d1,t1);
        ui->dateTimeEdit->setDateTime(qdt);
        //player=nullptr;
        videoWidget = new QVideoWidget;
        showVideo();
        ui->lineEdit_ID->setText(video_object->getID());
        ui->lineEdit_inspection->setText(video_object->getInspectionNo());
        ui->label_time->setText(video_object->getinstallTime());
        ui->label_lo->setText(video_object->getLO());
        ui->label_la->setText(video_object->getLA());
}

void Dialog::showVideo()
{
    QDateTime currdatetime=ui->dateTimeEdit->dateTime();
    QSqlQuery video_q(videodata);
    video_q.exec(QString("select * from video where equipmentID='%1';").arg(video_object->getID()));
    QDateTime t;
    QString videopath;
    while (video_q.next()) {
        qDebug()<<video_q.record().value(0).toString();
        t = QDateTime::fromString(video_q.record().value(0).toString(),"yyyy-MM-dd hh");
        if(currdatetime.toSecsSinceEpoch()==t.toSecsSinceEpoch()){
            videopath=video_q.record().value(2).toString();break;
        }
    }
    delete videoWidget;
    videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);
    player->setMedia(QUrl::fromLocalFile(videopath)); // 该路径换为自己的视频路径
    videoWidget->show();
    player->play();
    ui->verticalLayout->addWidget(videoWidget);
    connect(player,SIGNAL(stateChanged(QMediaPlater::State)),this,SLOT(mediaStateChanged(QMediaPlayer::State)));
    //2 播放进度信号变化函数
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    //3 播放长度信号变化
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
    //4 设置播放错误关联
    connect(player,SIGNAL(error(QMediaPlayer::Error)),this,SLOT(handleError()));
    ui->pushButton_2->setToolTip(QString::fromLocal8Bit("play video"));

}

void Dialog::connectDataBase()
{
    videodata=QSqlDatabase::addDatabase("QSQLITE");
    videodata.setDatabaseName("..\\dayi_project_20210519\\videoData.db");
    if(!videodata.open()){
        QMessageBox::warning(this,tr("warning"),tr("video data base open failure!"),QMessageBox::Ok);
        return;
    }
    qDebug()<<"win";
}

void Dialog::play()
{
    switch (player->state()) {
    case QMediaPlayer::PlayingState:
        player->pause();
        break;
    default:
        player->play();
        break;
    }
}

void Dialog::mediaStateChanged(QMediaPlayer::State state)
{
    //player播放过程中动态调整播放速度
    switch (state) {
    case QMediaPlayer::PlayingState:
        ui->pushButton_2->setToolTip(QString::fromLocal8Bit("stop play video"));
        break;
    default:
        ui->pushButton_2->setToolTip(QString::fromLocal8Bit("play video"));
        break;
    }
}

void Dialog::positionChanged(qint64 position)
{
    ui->horizontalSlider->setValue(position);//改变播放
    QTime t_b=QTime::fromMSecsSinceStartOfDay(position);
    ui->label_b->setText(t_b.toString("hh:mm:ss"));
}

void Dialog::setPosition(int position)
{
    player->setPosition(position);//获取play进度条调整
    QTime t_b=QTime::fromMSecsSinceStartOfDay(position);
    ui->label_b->setText(t_b.toString("hh:mm:ss"));
}

void Dialog::durationChanged(qint64 duration)
{
    QTime end_t;
    ui->horizontalSlider->setRange(0,duration);//获取进度条的长度
    qDebug()<<duration;
    end_t=QTime::fromMSecsSinceStartOfDay(duration);
    ui->label_e->setText(end_t.toString("hh:mm:ss"));
}

void Dialog::handleError()
{
    ui->pushButton_2->setEnabled(false);
}

Dialog::~Dialog()
{
    delete ui;
    delete  player;
    delete  videoWidget;
}

void Dialog::on_pushButton_clicked()
{
    showVideo();

    qDebug()<<"search"<<endl;
}




void Dialog::on_pushButton_finish_clicked()
{
    if(video_object->getID()==ui->lineEdit_ID->text()&&video_object->getInspectionNo()==ui->lineEdit_inspection->text()){
        qDebug()<<"no change!";
        return ;
    }
    QSqlQuery t_video(p->get_equipmentData());
    if(video_object->getID()!=ui->lineEdit_ID->text()){
        t_video.exec(QString("select count(*) from equipment where id='%1';").arg(ui->lineEdit_ID->text()));
        t_video.next();
        int c1=t_video.value(0).toInt();
        qDebug()<<c1;
        if(c1>0){
            //说明有了相同的ID
            QMessageBox::warning(this,tr("warning"),tr("has same id in data base!"),QMessageBox::Ok);
            ui->lineEdit_ID->setText(video_object->getID());//改回
        }else{

            t_video.exec(QString("update equipment set id='%1' where id='%2';").arg(ui->lineEdit_ID->text()).arg(video_object->getID()));
            video_object->setNum(ui->lineEdit_ID->text());
            qDebug()<<"change id";
        }
    }

    if(video_object->getInspectionNo()!=ui->lineEdit_inspection->text()){
        QSqlQuery inspe_t(p->get_inspectionData());
        inspe_t.exec(QString("select count(*) from inspection where id='%1';").arg(ui->lineEdit_inspection->text()));
        inspe_t.next();
        int c2=inspe_t.value(0).toInt();
        if(c2<=0){
            QMessageBox::warning(this,tr("warnig"),tr("has not this inspection!"),QMessageBox::Ok);
            ui->lineEdit_inspection->setText(video_object->getInspectionNo());
        }else{
            //目标的检测点没有安装那个kindName
            t_video.exec(QString("select count(*) from equipment where inspectionPointNo='%1' and kindName = 'monitor' ;").arg(ui->lineEdit_inspection->text()));
            t_video.next();
            int count_inspection_equipment=t_video.value(0).toInt();
            if(count_inspection_equipment>=1){
                QMessageBox::warning(this,tr("warning"),tr("Target detection point full!"),QMessageBox::Ok);
                ui->lineEdit_inspection->setText(video_object->getInspectionNo());
                return;
            }else {
             //改所在的检测点编号,经度，纬度
            t_video.exec(QString("update equipment set inspectionPointNo='%1' where id='%2'; ").arg(ui->lineEdit_inspection->text()).arg(video_object->getID()));
            inspe_t.exec(QString("select * from inspection where id='%1';").arg(ui->lineEdit_inspection->text()));
            inspe_t.next();
            QString lo=inspe_t.value(2).toString();
            QString la=inspe_t.value(3).toString();
            t_video.exec(QString("update equipment set Longitude='%1' where id='%2'; ").arg(lo).arg(video_object->getID()));
            t_video.exec(QString("update equipment set Latitude='%1' where id='%2'; ").arg(la).arg(video_object->getID()));
            video_object->setLO(lo);
            video_object->setLA(la);
            video_object->setInspectionNo(ui->lineEdit_inspection->text());
            ui->label_lo->setText(lo);
            ui->label_la->setText(la);
            qDebug()<<"change finish!";
}
        }
    }
    if(p->get_equipmentModel()!=nullptr)
    (p->get_equipmentModel())->submitAll();
}

void Dialog::on_comboBox_currentIndexChanged(int index)
{
    QSqlQuery t(p->get_equipmentData());
    t.exec(QString("update equipment set state = %1 where id='%2';").arg(QString::number(1-index)).arg(video_object->getID()));
    state=1-index;
    video_object->set_state(state);
    if(p->get_equipmentModel()!=nullptr)
    (p->get_equipmentModel())->submitAll();
}

void Dialog::on_pushButton_2_clicked()
{
    play();
}

void Dialog::on_horizontalSlider_sliderMoved(int position)
{
    setPosition(position);
}
