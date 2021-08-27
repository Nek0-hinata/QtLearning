#include "database.h"
#include "QMessageBox"
#include "md5.h"
#include "fstream"
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
        userName = user;
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

void DataBase::consume(QString id, QString money, QString loc, bool isIn) {
    QSqlQuery q(db);
    QSqlQuery temp = find(id);
    if (temp.next()) {
        if (isIn) {
            q.prepare("INSERT INTO card_log (user_id, user_name, in_cash, location) values (:id, :name, :money, :loc)");
            if (temp.value(4).toDouble() - money.toDouble() <= 0) {
                QMessageBox::critical(NULL, "妈的", "还想白嫖？");
                return;
            }
        } else {
            q.prepare("INSERT INTO card_log (user_id, user_name, out_cash, location) values (:id, :name, :money, :loc)");
            if (temp.value(5).toDouble() - money.toDouble() <= 0) {
                QMessageBox::critical(NULL, "妈的", "还想白嫖？");
                return;
            }
        }
        QString name = temp.value(2).toString();
        q.bindValue(":id", id);
        q.bindValue(":name", name);
        q.bindValue(":money", "-" + money);
        q.bindValue(":loc", loc);
        q.exec();
        double num = 0;
        if (!isIn) {
            num = temp.value(5).toDouble();
            num -= money.toDouble();
            q.prepare("UPDATE user_base SET user_outcash=:money WHERE user_id=:id ;");
            q.bindValue(":money", num);
            q.bindValue(":id", id);
            q.exec();
        } else {
            num = temp.value(4).toDouble();
            num -= money.toDouble();
            q.prepare("UPDATE user_base SET user_incash=:money WHERE user_id=:id ;");
            q.bindValue(":money", num);
            q.bindValue(":id", id);
            q.exec();
        }
        QMessageBox::information(NULL, "想要被投币", "消费成功！ 您的卡内余额为： " + QString::fromStdString(std::to_string(num)));
    }
}

void DataBase::changePwd(QString pwd) {
    QSqlQuery q(db);
    q.prepare("UPDATE admin_list SET admin_pwd=:pwd WHERE admin_name=:name ;");
    q.bindValue(":pwd", QString::fromStdString(md5(pwd.toStdString())));
    q.bindValue(":name", userName);
    q.exec();
}

void DataBase::changeLoss(QString id, QString user, bool isBack) {
    QSqlQuery q(db);
    QSqlQuery temp = find(id);
    if (temp.next()) {
        if (temp.value(0).toString() == id && temp.value(2).toString() == user) {
            q.prepare("UPDATE user_base SET user_loss=:status WHERE user_id=:id ;");
            int status = 0;
            if (isBack) status = 0;
            else status = 1;
            q.bindValue(":status", QString::fromStdString(std::to_string(status)));
            q.bindValue(":id", id);
            q.exec();
            QMessageBox::information(NULL, "啊呀", isBack ? "我出狱了！" : "md我进去了");
            return;
        } else {
            QMessageBox::critical(NULL, "不对劲！", "暗号错误，有内鬼！");
            return;
        }
    } else {
        QMessageBox::critical(NULL, "不对啊", "压根不存在！");
    }
}

void DataBase::deleteCard(QString id, QString user) {
    QSqlQuery q(db);
    QSqlQuery temp = find(id);
    if (temp.next()) {
        if (temp.value(0).toString() == id && temp.value(2).toString() == user) {
            q.prepare("DELETE FROM card_log WHERE user_id=:id; \n"
                        "DELETE FROM user_base WHERE user_id=:id; ");
            q.bindValue(":id", id);
            q.exec();
            QMessageBox::information(NULL, "啊呀", "又一个鲜活的小伙伴永远的离开了我们");
            return;
        } else {
            QMessageBox::critical(NULL, "不对劲！", "暗号错误，有内鬼！");
            return;
        }
    }
}

bool DataBase::setting(QString host, QString user, int port, QString database, QString pwd) {
    using namespace std;
    ofstream out;
    out.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\flash.dat)", ios::out | ios::trunc);
    db.setHostName(host);
    db.setDatabaseName(database);
    db.setPassword(pwd);
    db.setUserName(user);
    db.setPort(port);
    out << host.toStdString() << " " << user.toStdString() << " " << to_string(port) << " " << database.toStdString() << endl;
    qDebug() << "开始连接";
    db.open();
    if(!db.open())
    {
        qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
        QMessageBox::critical(NULL, "警告", "无法连接到数据库，请检查您的配置是否正确");
        out.close();
        return false;
    }
    else
    {
        qDebug()<<"连接成功";
        out.close();
        return true;
    }
}
