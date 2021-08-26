#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminlist.h"
#include "listclass.h"
#include <QMessageBox>

extern AdminList AL;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionsearching_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->search_ui);
}


void MainWindow::on_actiontongji_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->tongji_ui);
}


void MainWindow::on_actionluru_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->luru_ui);
}


void MainWindow::on_actionzhuce_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->zhuce_ui);
}


void MainWindow::on_pushButton_3_clicked()
{
    if (ui->password1->text() != ui->password2->text()) {
        QMessageBox::warning(this, "warning", "The two passwords are inconsistent", QMessageBox::Yes);
    } else {
        AL.add(ui->userName->text().toStdString(), ui->password1->text().toStdString());
    }
    ui->userName->clear();
    ui->password1->clear();
    ui->password2->clear();
    ui->userName->setFocus();
}


void MainWindow::on_pushButton_4_clicked()
{
    if (ui->password1->text() != ui->password2->text()) {
        QMessageBox::warning(this, "warning", "The two passwords are inconsistent", QMessageBox::Yes);
    } else {
        AL.del(ui->userName->text().toStdString(), ui->password1->text().toStdString());
    }
    ui->userName->clear();
    ui->password1->clear();
    ui->password2->clear();
    ui->userName->setFocus();
}

