#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminlist.h"
#include "listclass.h"
#include <QMessageBox>

extern AdminList AL;
extern ListClass LC;
string KINDS[4] = {"Teacher", "Student", "Temp", "Other"};

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_actionsearching_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->search_ui);
}


void MainWindow::on_actiontongji_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->tongji_ui);
}


void MainWindow::on_actionluru_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->luru_ui);
}


void MainWindow::on_actionzhuce_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->zhuce_ui);
}


void MainWindow::on_pushButton_3_clicked() {
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


void MainWindow::on_pushButton_4_clicked() {
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


void MainWindow::on_pushButton_2_clicked() {
    string I = KINDS[ui->kinds->currentIndex()] + " " + ui->name->text().toStdString() + " " +
               ui->company->text().toStdString();
    LC.input(I);
    ui->name->clear();
    ui->company->clear();
}


void MainWindow::on_pushButton_clicked()
{
    stringstream ss;
    ss << LC.find(ui->searchLine->text().toStdString(), ui->searchingBox->currentIndex());
    string t;
    ss >> t;
    ui->textBrowser->setText(QString::fromStdString(t));
    ss >> t;
    ui->textBrowser_2->setText(QString::fromStdString(t));
    ss >> t;
    ui->textBrowser_3->setText(QString::fromStdString(t));
    ss >> t;
    ui->textBrowser_4->setText(QString::fromStdString(t));
    ss >> t;
    ui->textBrowser_5->setText(QString::fromStdString(t));
    ss >> t;
    ui->textBrowser_6->setText(QString::fromStdString(t));
    ss >> t;
    ui->textBrowser_7->setText(QString::fromStdString(t));
    ss >> t;
    ui->textBrowser_8->setText(QString::fromStdString(t));
    ss.clear();
    t.clear();
}


void MainWindow::on_pushButton_5_clicked()
{
    LC.resetPtr();
    QMessageBox::information(this, "震惊", "你已经把锚点重置了！");
}

