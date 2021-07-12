#ifndef DATASEARCH_H
#define DATASEARCH_H
#include"ui_datasearch.h"
#include"mainwindow.h"
#include<QObject>
#include<QMainWindow>

namespace Ui { class DataSearchFace; }


class DataSearchFace{
    Q_OBJECT

public:
    explicit DataSearchFace(QMainWindow*p=nullptr);
    ~DataSearchFace();
private:
    Ui::DataSearchFace *ui;
};

#endif // DATASEARCH_H
