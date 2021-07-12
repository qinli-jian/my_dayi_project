#ifndef ADDNEWEQUIPMENTDIALOG_H
#define ADDNEWEQUIPMENTDIALOG_H
#include"mainwindow.h"
#include <QDialog>
#include<QSqlRecord>
namespace Ui {
class addNewEquipmentDialog;
}

class addNewEquipmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addNewEquipmentDialog(QString lo,QString la,QString inspectionID,QMainWindow *parent = nullptr);
    ~addNewEquipmentDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addNewEquipmentDialog *ui;
    QMainWindow *p;
    QString curInspectionID;
    QString LO;
    QString LA;
};

#endif // ADDNEWEQUIPMENTDIALOG_H
