#ifndef SHOWEQUIPMENTDIALOG_H
#define SHOWEQUIPMENTDIALOG_H

#include <QDialog>
#include"mainwindow.h"
#include<QSqlTableModel>
#include"FourGProbe.h"
#include"LicensePlateMonitoring.h"
#include"VideoSurveillance.h"
#include"readonlyClass.h"
class FourGProbe;
class LicensePlateMonitoring;
class VideoSurveillance;
class MainWindow;
namespace Ui {
class showEquipmentDialog;
}

class showEquipmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit showEquipmentDialog(MainWindow *parent = nullptr);
    void Refresh_total_tab();
    ~showEquipmentDialog();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::showEquipmentDialog *ui;
    QSqlTableModel *equip_model;
    MainWindow*p;
    ReadOnlyDelegate read_only;
};

#endif // SHOWEQUIPMENTDIALOG_H
