#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QString>

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
    if (ui->userLineEdit->text() == tr("admin") &&
            ui->pwdLineEdit->text() == tr("123456"))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, QString::fromUtf8("Login Failed"), QString::fromUtf8("Username doesn't exist or password is wrong!"),
            QMessageBox::Yes);
        this->show();
        ui->userLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->userLineEdit->setFocus();
    }
}

void LoginDialog::on_exitBtn_clicked()
{

}

