#include "cartimesearch.h"
#include "ui_cartimesearch.h"

cartimesearch::cartimesearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cartimesearch)
{
    ui->setupUi(this);
//    ui->tableWidget->inser
}

cartimesearch::~cartimesearch()
{
    delete ui;
}
