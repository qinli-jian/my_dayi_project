#include"AddDialog.h"
#include<QDebug>

AddDialog::AddDialog(QWidget*p):QDialog(p){

    this->p=(MainWindow*)p;
    QDialog::setWindowTitle("Setting property interface");
    QDialog::setMinimumSize(400,400);
    QDialog::setMaximumSize(400,400);
    label = new QLabel(this);label->setObjectName("labelNum");
    label->move(5,50);label->setText(QString("Number:"));
    line = new QLineEdit(this);line->resize(250,30);line->setObjectName("lineNum");
    line->move(100,50);line->setText("00");

    label2 = new QLabel(this);label2->setObjectName("labelLAL");
    label2->move(5,100);label2->setText(QString("Latitude and longitude:"));

    line2 = new QLineEdit(this);line2->resize(100,30);line2->setObjectName("line2LA");
    line2->move(100,150);line2->setText("00");

    line3 = new QLineEdit(this);line3->resize(100,30);line3->setObjectName("line3LO");
    line3->move(250,150);line3->setText("00");

    confirm_p=new QPushButton(this);

    confirm_p->setObjectName(tr("confirmP"));
    confirm_p->setText("Confirm");
    confirm_p->move(100,350);

    cancel_p=new QPushButton(this);cancel_p->setObjectName("cancelP");
    cancel_p->setText("Cancel");
    cancel_p->move(250,350);


    QMetaObject::connectSlotsByName(this);
}

AddDialog::~AddDialog(){
    delete line;
    delete line2;
    delete line3;
    delete this->label;
    delete this->label2;
    delete this->cancel_p;
    delete this->confirm_p;
}

void AddDialog::on_confirmP_clicked(){

}

void AddDialog::on_cancelP_clicked(){

    this->close();
}
