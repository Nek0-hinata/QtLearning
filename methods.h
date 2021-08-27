#ifndef METHODS_H
#define METHODS_H

#include <QDialog>

namespace Ui {
class Methods;
}

class Methods : public QDialog
{
    Q_OBJECT

public:
    explicit Methods(QWidget *parent = nullptr);
    ~Methods();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Methods *ui;
};

#endif // METHODS_H
