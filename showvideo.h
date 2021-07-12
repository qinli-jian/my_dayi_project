#ifndef SHOWVIDEO_H
#define SHOWVIDEO_H

#include <QDialog>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QTime>
namespace Ui {
class showVideo;
}

class showVideo : public QDialog
{
    Q_OBJECT

public:
    explicit showVideo(QString path,QWidget *parent = nullptr);

    ~showVideo();

private slots:
    void play();
    void mediaStateChanged(QMediaPlayer::State state);//播放状态
    void positionChanged(qint64 position);//获取播放位置
    void setPosition(int position);//获取播放位置
    void durationChanged(qint64 duration);//播放长度
    void handleError();//播放异常

    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_clicked();

private:
    Ui::showVideo *ui;
    QString path;
    void init();
    QMediaPlayer *mediaPlayer;

    QVideoWidget *videoWidget;
};

#endif // SHOWVIDEO_H
