#include "sets.h"
#include "ui_sets.h"
#include "database.h"
#include "fstream"
#include "sstream"
#include "QMessageBox"

extern DataBase DB;

Sets::Sets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sets)
{
    ui->setupUi(this);
    using namespace std;
    ifstream in;
    in.open("./data/flash.dat", ios::in | ios::ate);
    if (!in.is_open()) {
        fstream wrt;
        wrt.open("./data/flash.dat", ios::in | ios::out | ios::trunc);
        QMessageBox::critical(this, "严重错误", "关键文件缺失，如果您是第一次弹出此窗口，请重启程序！\n否则请在exe目录下手动创建data文件夹");
        wrt.close();
    }
    in.seekg(0, ios::beg);
    stringstream ss;
    string s;
    getline(in, s);
    ss << s;
    string t;
    ss >> t;
    ui->host->setText(QString::fromStdString(t));
    t.clear();
    ss >> t;
    ui->user->setText(QString::fromStdString(t));
    t.clear();
    ss >> t;
    ui->port->setText(QString::fromStdString(t));
    t.clear();
    ss >> t;
    ui->database->setText(QString::fromStdString(t));
}

Sets::~Sets()
{
    delete ui;
}

void Sets::on_pushButton_clicked()
{
    if (DB.setting(ui->host->text(), ui->user->text(), ui->port->text().toInt(), ui->database->text(), ui->password->text())) {
        accept();
    } else {
        reject();
    }
}

