#include "methods.h"
#include "ui_methods.h"
extern bool isMysql;
Methods::Methods(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Methods)
{
    ui->setupUi(this);
}

Methods::~Methods()
{
    delete ui;
}

void Methods::on_pushButton_clicked()
{
    isMysql = true;
    accept();
}


void Methods::on_pushButton_3_clicked()
{
    isMysql = false;
    reject();
}

