#ifndef DIALOG_H
#define DIALOG_H
//#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include<QMainWindow>
#include "VideoSurveillance.h"
#include<QSqlDatabase>

class VideoSurveillance;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(VideoSurveillance *video_object = nullptr,QMainWindow*p=nullptr);
    void showVideo();
    void connectDataBase();

    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_finish_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();
    void play();
    void mediaStateChanged(QMediaPlayer::State state);//播放状态
    void positionChanged(qint64 position);//改变播放位置
    void setPosition(int position);//获取播放位置
    void durationChanged(qint64 duration);//播放长度
    void handleError();//播放异常的抛出



    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::Dialog *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    MainWindow*p;
    VideoSurveillance*video_object;
    QSqlDatabase videodata;
    int state;
};

#endif // DIALOG_H
