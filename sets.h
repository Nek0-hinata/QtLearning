#ifndef SETS_H
#define SETS_H

#include <QDialog>

namespace Ui {
class Sets;
}

class Sets : public QDialog
{
    Q_OBJECT

public:
    explicit Sets(QWidget *parent = nullptr);
    ~Sets();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Sets *ui;
};

#endif // SETS_H
