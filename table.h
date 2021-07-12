#ifndef TABLE_H
#define TABLE_H

#include <QWidget>

namespace Ui {
class table;
}

class table : public QWidget
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = 0);
    ~table();

private:
    Ui::table *ui;
};

#endif // TABLE_H
