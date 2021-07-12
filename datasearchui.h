#ifndef DATASEARCHUI_H
#define DATASEARCHUI_H

#include <QMainWindow>
#include"mainwindow.h"
#include<QSqlDatabase>
#include"readonlyClass.h"
#include"showvideo.h"
namespace Ui {
class DataSearchui;
}

class DataSearchui : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataSearchui(MainWindow *parent = nullptr);
    ~DataSearchui();

    void show_peopleflow();
    void show_carflow();
    void video_data();
    void set_total();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_name_clicked();

    void on_searchbytime_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::DataSearchui *ui;
    MainWindow*p_main;

    QSqlTableModel*allcardata_model;
    QSqlTableModel*allpeopledata_model;
    QSqlTableModel*video_model;

    ReadOnlyDelegate read_only;
    QSqlDatabase car_database;
    QSqlDatabase people_database;
    QSqlDatabase video_database;
};

#endif // DATASEARCHUI_H
