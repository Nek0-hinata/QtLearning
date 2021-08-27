#include "database.h"
#include "QMessageBox"
#include "md5.h"
#include "QtDebug"
DataBase::DataBase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("schoolqt");
    db.setUserName("root");
    db.setPassword("B79W55H78");
    qDebug() << "开始连接";
    db.open();
    if(!db.open())
    {
        qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
        return;
    }
    else
    {
        qDebug()<<"连接成功";
        this->init();
    }
}

void DataBase::init() {
    QSqlQuery q(db);
    q.exec("create table if not exists `admin_list` (`admin_id` INT unique auto_increment PRIMARY KEY,`admin_name` VARCHAR(20) UNIQUE NOT NULL,`admin_pwd` VARCHAR(512) NOT NULL);");
    q.exec("select * from admin_list");
    if (!q.next()) {
        q.prepare("INSERT INTO admin_list(admin_name, admin_pwd) values (?, ?);");
        q.addBindValue("admin");
        q.addBindValue("e10adc3949ba59abbe56e057f20f883e");
    }
    qDebug() << "初始化成功";
}

QSqlQuery DataBase::getConnection() {
    QSqlQuery q(db);
    return q;
}

bool DataBase::verify(QString user, QString pwd) {
    QSqlQuery q(db);
    q.prepare("SELECT * FROM admin_list WHERE admin_name=:user AND admin_pwd=:pwd; ");
    q.bindValue(":user", user);
    q.bindValue(":pwd", QString::fromStdString(md5(pwd.toStdString())));
    q.exec();
    if (q.next()) {
        qDebug() << "密码正确";
        return true;
    } else {
        return false;
    }
}

void DataBase::addAdmin(QString user, QString pwd) {
    QSqlQuery q(db);
    q.prepare("SELECT * FROM admin_list WHERE admin_name=:user");
    q.bindValue(":user", user);
    q.exec();
    if (q.next()) {
        QMessageBox::warning(NULL, "警告！", "该用户已存在");
    } else {
        q.prepare("INSERT INTO admin_list(admin_name, admin_pwd) values (:user, :pwd)");
        q.bindValue(":user", user);
        q.bindValue(":pwd", pwd);
        q.exec();
    }
}

void DataBase::deleteAdmin(QString user, QString pwd) {
    QSqlQuery q(db);
    q.prepare("DELETE FROM admin_list WHERE admin_name=:user AND admin_pwd=:pwd");
    q.bindValue(":user", user);
    q.bindValue(":pwd", pwd);
    q.exec();
}
