#include "showvideo.h"
#include "ui_showvideo.h"

showVideo::showVideo(QString path,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showVideo)
{
    ui->setupUi(this);
    this->path=path;
    //创建mediaplay
    mediaPlayer=new QMediaPlayer(this);
//    mediaPlayer->setVideoOutput(ui);
    videoWidget = new QVideoWidget;
    mediaPlayer->setVideoOutput(videoWidget);
    mediaPlayer->setMedia(QUrl::fromLocalFile(path)); // 该路径换为自己的视频路径
    videoWidget->show();
    mediaPlayer->play();
    ui->verticalLayout->addWidget(videoWidget);
    //监听信号变化函数
    connect(mediaPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(mediaStateChanged(QMediaPlayer::State)));
    //播放 进度信号变化函数
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    //播放长度信号变化
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
    //设置播放错误关联
    connect(mediaPlayer,SIGNAL(error(QMediaPlayer::Error)),this,SLOT(handleError()));

}

showVideo::~showVideo()
{
    delete ui;
}

void showVideo::play()
{
    switch (mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        break;
    default:
        mediaPlayer->play();
        break;
    }
}

void showVideo::mediaStateChanged(QMediaPlayer::State state)
{
    //mediaPlayer播放过程中动态调整播放进度
    switch (state) {
    case QMediaPlayer::PlayingState:
        ui->pushButton->setToolTip(QString::fromLocal8Bit("pause this video"));
        break;
    default:
        ui->pushButton->setToolTip(QString::fromLocal8Bit("play this video"));
        break;
    }
}

void showVideo::positionChanged(qint64 position)
{
    QTime t;
    t=QTime::fromMSecsSinceStartOfDay(position);
    ui->label->setText(t.toString("hh:mm:ss"));
    ui->horizontalSlider->setValue(position);
}

void showVideo::setPosition(int position)
{
    mediaPlayer->setPosition(position);
}

void showVideo::durationChanged(qint64 duration)
{
    QTime t;
    t=QTime::fromMSecsSinceStartOfDay(duration);
    ui->label_2->setText(t.toString("hh:mm:ss"));
    ui->horizontalSlider->setRange(0,duration);
}

void showVideo::handleError()
{
    ui->pushButton->setEnabled(false);
}

void showVideo::on_horizontalSlider_sliderMoved(int position)
{
    setPosition(position);
}

void showVideo::on_pushButton_clicked()
{
   play();

}
