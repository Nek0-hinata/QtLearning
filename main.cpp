#include "mainwindow.h"
#include "logindialog.h"
#include "fstream"
#include <QApplication>

int MAXID;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog login;
    std::ifstream idF;
    idF.open("/data/ID.dat");
    if (idF.is_open()) {
        std::string temp;
        if (std::getline(idF, temp)) {
            MAXID = std::stoi(temp);
        } else {
            MAXID = 1;
        }
    }
    idF.close();
    if (login.exec()==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
