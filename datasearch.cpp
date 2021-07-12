#include"DataSearchFace.h"

/*
 * MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
*/
DataSearchFace::DataSearchFace(QMainWindow*p)
{
    ui=new Ui::DataSearchFace;
    ui->setupUi(p);
}
DataSearchFace::~DataSearchFace(){

}
