#ifndef FOURGFACING_H
#define FOURGFACING_H

#include <QDialog>
#include"mainwindow.h"
#include"FourGProbe.h"
#include<QRegExpValidator>
#include<QVector>
#include<QtCharts>
#include<QtCharts/QBarSet>
#include<QValueAxis>
#include"people_search.h"
#include"randomdata.h"
#include<QCloseEvent>
QT_CHARTS_USE_NAMESPACE
class FourGProbe;
class MainWindow;
class people_search;
namespace Ui {
class fourGfacing;
}

class fourGfacing : public QDialog
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent*event);

public:
    explicit fourGfacing(QMainWindow*parent,FourGProbe *four_onject);
    ~fourGfacing();
    void statistics();
    void initDraw();

private slots:
    void on_pushButton_3_clicked();

    void DrawLine();
    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_comboBox_statu_currentIndexChanged(int index);

private:
    Ui::fourGfacing *ui;
    MainWindow*p;
    FourGProbe*four_onject;
    QChart*chart_t;
    int x_count;
    QLineSeries *lineseries;
    QBarSeries *barseries;

    QTimer *timer;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    int state;
    people_search*p_widget;

};

#endif // FOURGFACING_H
