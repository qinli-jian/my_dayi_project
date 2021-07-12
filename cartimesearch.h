#ifndef CARTIMESEARCH_H
#define CARTIMESEARCH_H

#include <QDialog>

namespace Ui {
class cartimesearch;
}

class cartimesearch : public QDialog
{
    Q_OBJECT

public:
    explicit cartimesearch(QWidget *parent = nullptr);
    ~cartimesearch();

private:
    Ui::cartimesearch *ui;
};

#endif // CARTIMESEARCH_H
