#ifndef PEOPLE_SEARCH_H
#define PEOPLE_SEARCH_H

#include <QDialog>
#include"mainwindow.h"
class MainWindow;
class FourGProbe;
namespace Ui {
class people_search;
}

class people_search : public QDialog
{
    Q_OBJECT

public:
    explicit people_search(FourGProbe*p_prode,MainWindow *parent = nullptr);
    ~people_search();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::people_search *ui;
    FourGProbe *p_prode;
    MainWindow *p_main;

    QSqlTableModel*people_model;
    QSqlDatabase p_da;
};

#endif // PEOPLE_SEARCH_H
