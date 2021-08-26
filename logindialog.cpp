#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QString>
#include "adminlist.h"

extern AdminList AL;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    if (AL.find(ui->userLineEdit->text().toStdString(), ui->pwdLineEdit->text().toStdString()))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, QString::fromUtf8("Login Failed"), QString::fromUtf8("user name or password error!"),
            QMessageBox::Yes);
        ui->userLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->userLineEdit->setFocus();
    }
}

void LoginDialog::on_exitBtn_clicked()
{

}

