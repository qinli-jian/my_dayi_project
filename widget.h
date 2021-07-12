#ifndef WIDGET_H
#define WIDGET_H
#include<QtCharts/QChart>
#include<QtCharts/QLineSeries>
#include<QtCharts/QSplineSeries>
#include<QtCharts/QBarSeries>
#include<QtCharts/QDateTimeAxis>
QT_CHARTS_USE_NAMESPACE
#include <QDialog>
#include<cardata_searchface.h>
#include"mainwindow.h"
#include"LicensePlateMonitoring.h"
#include<QtMath>
#include<QDateTime>
#include<QTime>
#include<QVector>
#include<QBarSet>
#include<QValueAxis>
#include"randomdata.h"
#include<QCloseEvent>
class MainWindow;
namespace Ui {
class Widget;
}
class FourGProbe;
class LicensePlateMonitoring;
class Widget : public QDialog
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent*event);
public:
    explicit Widget( LicensePlateMonitoring*lp,QWidget *parent = 0);
    LicensePlateMonitoring *get_lp_object();
    int statistics();
    void initDraw();
    ~Widget();

private slots:
    void DrawLine();

    void on_pushButton_clicked();

    void on_lineEdit_id_returnPressed();

    void on_lineEdit_inspection_editingFinished();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
    LicensePlateMonitoring *lp_object;
    MainWindow*p;
    QSqlDatabase car_flow;
    QChart*chart ;
    QChart::ChartType *chartType;
    QLineSeries *lineseries;
    QBarSeries *barseries;
    QChart *mchart;
    int count;
    int state;
    QTimer *timer;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
};

#endif // WIDGET_H
