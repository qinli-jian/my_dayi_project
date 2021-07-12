#ifndef ADDNEWISPECTIONDIALOG_H
#define ADDNEWISPECTIONDIALOG_H

#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class addNewIspectionDialog;
}

class addNewIspectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addNewIspectionDialog(QWidget *parent = nullptr);
    ~addNewIspectionDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addNewIspectionDialog *ui;
    QMainWindow*p;
};

#endif // ADDNEWISPECTIONDIALOG_H
