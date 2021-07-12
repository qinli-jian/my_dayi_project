#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include"mainwindow.h"
#include<QDialog>
class AddDialog:public QDialog{

Q_OBJECT

public:
    AddDialog(QWidget*p=nullptr);
    ~AddDialog();

private:
    QPushButton * cancel_p;
     QPushButton *confirm_p;
     QLineEdit * line3;
     QLineEdit * line2;
      QLabel*label2;
      QLineEdit * line;
      QLabel*label;
      QMainWindow*p;
private slots:
      void on_confirmP_clicked();
      void on_cancelP_clicked();
signals:
      void confirm_s(QStringList);
};

#endif // ADDDIALOG_H
