#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <string>
#include "QString"


using namespace std;

class DataBase
{
public:
    DataBase();

    QSqlQuery getConnection();

    bool setting(QString host, QString user, int port, QString database, QString pwd);

    bool verify(QString user, QString pwd);  //验证合法性

    void addAdmin(QString user, QString pwd);  //添加管理员

    void deleteAdmin(QString user, QString pwd);  //删除管理员

    void addCard(QString kinds, QString name, QString company);   //增加一个卡片

    void charge(QString id, QString money, QString kinds);   //充值

    void consume(QString id, QString money, QString loc, bool isIn);   //两种消费

    void changePwd(QString pwd);  //改密

    void changeLoss(QString id, QString user, bool isBack);

    void deleteCard(QString id, QString user);

    QSqlQuery find(QString id);   //根据id找整行user

    bool legal(QString id);

    QString ReturnUser() {return userName;}

private:
    void init();

    QSqlDatabase db;

    QString userName;
};

#endif // DATABASE_H
