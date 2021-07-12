#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QSqlTableModel>
#include <QMainWindow>
#include<QMediaPlayer>
#include<QPushButton>
#include<QDebug>
#include<QWidget>
#include<QLineEdit>
#include<QLabel>
#include<QDialog>
#include<QTableWidget>
#include"Equipment.h"
#include"MonitoringPoint.h"
#include"widget.h"
#include"FourGProbe.h"
#include"Road.h"
#include"AddDialog.h"
#include<QObject>
#include"RoadInformationWidget.h"
#include<QFont>
#include<QMessageBox>
#include<QDateTime>
#include"datasearchui.h"
#include<QTableView>
#include<QSqlDatabase>
#include"ConnectDataBase.h"

#include"addnewispectiondialog.h"
#include<QSqlQuery>
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QModelIndex>
#include"addnewequipmentdialog.h"
#include"showequipmentdialog.h"
#include"VideoSurveillance.h"
#include"randomdata.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class QSqlTableModel;
class QMediaPlayer;
class QVideoWidget;
class Road;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:



    MainWindow(QWidget *parent = nullptr);
    bool ConnectDataBase();
    QSqlTableModel* getInspectionModel();
    QSqlTableModel*get_equipmentModel();

    QSqlDatabase& get_inspectionData();
    QSqlDatabase& get_equipmentData();
    QSqlDatabase& get_peopleflowData();
    QSqlDatabase&get_carflowData();
    MonitoringPoint*get_inspection();
    QModelIndex get_quip_index();
    void changeData(int f);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();


    void on_pushButton_4_clicked();


    void on_deletepushButton_clicked();

    void on_MainWindow_destroyed();

    void on_pushButton_3_clicked();

    void on_pushButton_submit_clicked();

    void on_pushButton_2_clicked();

    void on_SearchpushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_AddEquipmentpushButton_clicked();

    void on_DeleteEquipmentpushButton_clicked();

    void on_pushButton_6_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_lineEdit_id_editingFinished();

    void on_lineEdit_lo_editingFinished();

    void on_lineEdit_la_editingFinished();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

private:
    QModelIndex index;
    QFont *allf ;
    Road *road;
    Ui::MainWindow *ui;
    QMediaPlayer * player;
    QSqlTableModel*inspectiondataModel;//检测点
    QSqlTableModel*equipment_Model;

    QSqlDatabase roadData;//道路数据
    QSqlDatabase inspectionPointData ;//检测点数据
    QSqlDatabase equipmentData;//设备数据
    QSqlDatabase passegerflowData;//人流数据
    QSqlDatabase trafficData;//车流数据
    QSqlDatabase monitirData;//视频数据

    MonitoringPoint*p_inspection;//检测点

    QModelIndex equipment_intdex;

signals:
    void seletedRow(int);

};


#endif // MAINWINDOW_H
