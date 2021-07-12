#include "table.h"
#include "ui_table.h"

table::table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);
}

table::~table()
{
    delete ui;
}
