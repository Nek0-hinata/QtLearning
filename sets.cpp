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
    in.open("E:\\Program_dev\\QtGui\\schoolWork\\schoolWork1\\data\\flash.dat", ios::in | ios::ate);
    if (!in.is_open()) {
        QMessageBox::critical(this, "严重错误", "无法打开文件夹，请检查路径是否正确，否则程序可能无法运行！");
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

