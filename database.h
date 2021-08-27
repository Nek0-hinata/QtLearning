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

    bool verify(QString user, QString pwd);

    void addAdmin(QString user, QString pwd);

    void deleteAdmin(QString user, QString pwd);

    void addCard(QString kinds, QString name, QString company);

private:
    void init();

    QSqlDatabase db;
};

#endif // DATABASE_H
