#ifndef CARDATA_SEARCHFACE_H
#define CARDATA_SEARCHFACE_H

#include <QDialog>
#include"mainwindow.h"
#include"FourGProbe.h"
#include<QSqlDatabase>
class MainWindow;
class LicensePlateMonitoring;
namespace Ui {
class cardata_searchface;
}

class cardata_searchface : public QDialog
{
    Q_OBJECT

public:
    explicit cardata_searchface(MainWindow*p1, QWidget *parent = nullptr);
    ~cardata_searchface();

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    //QSqlDatabase& prode_datat;
    Ui::cardata_searchface *ui;
    LicensePlateMonitoring *p_prode;
    MainWindow*p_main;
    QSqlTableModel* model;
//
};

#endif // CARDATA_SEARCHFACE_H
