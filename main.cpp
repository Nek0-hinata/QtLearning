#include "mainwindow.h"
#include "logindialog.h"
#include "fstream"
#include <QApplication>
#include "adminlist.h"
#include "database.h"
#include "listclass.h"
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtDebug>

bool isMysql = true;
long long MAXID;
long long CASHID;
AdminList AL;
ListClass LC;
DataBase DB;
//一卡通编号、种类（教工卡、学生卡、其它卡、临时卡）   基本信息
// 、姓名、单位、公交费金额、校内金额、挂失（1表示正常，0表示挂失，此内容选做），
// 有效性等信息。
//一卡通编号、充值金额、充值日期、操作员等    充值管理
//一卡通编号、消费编号、消费日期、消费金额、消费地点、消费人员等  消费管理
string GetTime() {
    time_t now = time(0);
    char dt[100];
    strftime(dt, sizeof(dt),"%Y-%m-%d_%H:%M:%S", localtime(&now));
    return dt;
}

void init();

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog login;
    std::ifstream idF;
    idF.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\ID.dat)", ios::in | ios::out | ios::ate);
    if (idF.is_open()) {
        std::string temp;
        idF.seekg(0, ios::beg);
        if (std::getline(idF, temp)) {
            MAXID = std::stoi(temp);
        } else {
            MAXID = 1;
        }
    }
    idF.close();
    idF.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\charge.dat)", ios::in | ios::out | ios::ate);
    if (idF.is_open()) {
        std::string temp;
        idF.seekg(0, ios::beg);
        if (std::getline(idF, temp)) {
            CASHID = std::stoi(temp);
        } else {
            CASHID = 1;
        }
    }
    idF.close();
    if (login.exec() == QDialog::Accepted) {
        w.show();
        return a.exec();
    } else {
        return 0;
    }
}

void init() {

}
