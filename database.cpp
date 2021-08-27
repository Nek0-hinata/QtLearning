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
    q.exec("create table if not exists `user_base` (\n"
           "`user_id` INT unique auto_increment PRIMARY KEY,\n"
           "`user_kinds` VARCHAR(20) NOT NULL ,\n"
           "`user_name` VARCHAR(20) NOT NULL,\n"
           "`user_company` VARCHAR(512) NOT NULL,\n"
           "`user_incash` INT DEFAULT 0,\n"
           "`user_outcash` INT  DEFAULT 0,\n"
           "`user_loss` BOOLEAN DEFAULT FALSE\n"
           ");");
    q.exec("create table if not exists `card_log` (\n"
           "`consume_id` INT unique auto_increment PRIMARY KEY,\n"
           "`user_id` INT NOT NULL,\n"
           "`user_name` VARCHAR(20)  NOT NULL,\n"
           "`in_cash` INT DEFAULT 0,\n"
           "`out_cash` INT DEFAULT 0,\n"
           "`location` VARCHAR(100) NOT NULL,\n"
           "`date` DATETIME DEFAULT now(),\n"
           "FOREIGN KEY (user_id)\n"
           "REFERENCES user_base(user_id)\n"
           ");");
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
        q.bindValue(":pwd", QString::fromStdString(md5(pwd.toStdString())));
        q.exec();
        QMessageBox::warning(NULL, "好耶！", "我们又新增了一名成员！");
    }
}

void DataBase::deleteAdmin(QString user, QString pwd) {
    QSqlQuery q(db);
    q.prepare("SELECT * FROM admin_list WHERE admin_name=:user");
    q.bindValue(":user", user);
    q.exec();
    if (q.next()) {
        q.prepare("SELECT admin_pwd FROM admin_list WHERE admin_name=:user");
        q.bindValue(":user", user);
        q.exec();
        q.next();
        if (q.value(0) == QString::fromStdString(md5(pwd.toStdString()))) {
            q.prepare("DELETE FROM admin_list WHERE admin_name=:user AND admin_pwd=:pwd");
            q.bindValue(":user", user);
            q.bindValue(":pwd", QString::fromStdString(md5(pwd.toStdString())));
            q.exec();
            QString t = "用户 " + user + " 已经永远的离开了我们！";
            QMessageBox::information(NULL, "哎呀", "该用户已经永远的离开了我们！", QMessageBox::Yes);
        } else {
            QMessageBox::warning(NULL, "坏了", "你是不是忘记密码了！", QMessageBox::Yes);
        }
    } else {
        QMessageBox::warning(NULL, "糟糕", "查无此人啊", QMessageBox::Yes);
    }
}

void DataBase::addCard(QString kinds, QString name, QString company) {
    QSqlQuery q(db);
    q.prepare("SELECT * FROM user_base WHERE user_name=:name AND user_company=:company");
    q.bindValue(":user", name);
    q.bindValue(":company", company);
    q.exec();
    if (!q.next()) {
        q.prepare("INSERT INTO user_base (user_kinds, user_name, user_company) values (:kinds, :name, :company)");
        q.bindValue(":kinds", kinds);
        q.bindValue(":name", name);
        q.bindValue(":company", company);
        q.exec();
        QString t = "已成功将用户 " + name + " 注册！";
        QMessageBox::information(NULL, "离征服世界又近了一步呢！", t , QMessageBox::Yes);
    } else {
        QMessageBox::information(NULL, "警告！", "本程序禁止影分身！", QMessageBox::Yes);
    }
}

bool DataBase::legal(QString id) {
    QSqlQuery q(db);
    q.prepare("SELECT user_loss FROM user_base WHERE user_id=:id ;");
    q.bindValue(":id", id);
    q.exec();
    if (q.next()) {
        if (q.value(0) == QString::fromStdString("1")) {
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

void DataBase::charge(QString id, QString money, QString kinds) {
    QSqlQuery q(db);
    QSqlQuery temp = find(id);
    if (temp.next()) {
        QString name = temp.value(2).toString();
        qDebug() << name << kinds << money;
        q.prepare("INSERT INTO card_log (user_id, user_name, in_cash, location) values (:id, :name, :money, :kinds)");
        q.bindValue(":id", id);
        q.bindValue(":name", name);
        q.bindValue(":money", money);
        q.bindValue(":kinds", kinds);
        q.exec();
        double num = 0;
        if (kinds == "公交一卡通") {
            num = temp.value(5).toDouble();
            num += money.toDouble();
            q.prepare("UPDATE user_base SET user_outcash=:money WHERE user_id=:id ;");
            q.bindValue(":money", num);
            q.bindValue(":id", id);
            q.exec();
        } else {
            num = temp.value(4).toDouble();
            num += money.toDouble();
            q.prepare("UPDATE user_base SET user_incash=:money WHERE user_id=:id ;");
            q.bindValue(":money", num);
            q.bindValue(":id", id);
            q.exec();
        }
        QMessageBox::information(NULL, "好消息！", "充值成功！ 您的卡内余额为： " + QString::fromStdString(std::to_string(num)));
    } else {
        QMessageBox::information(NULL, "啊啦", "您是不是眼花输错id了呢");
    }
}

QSqlQuery DataBase::find(QString id) {
    QSqlQuery q(db);
    q.prepare("SELECT * FROM user_base WHERE user_id=:id ;");
    q.bindValue(":id", id);
    q.exec();
    return q;
}
