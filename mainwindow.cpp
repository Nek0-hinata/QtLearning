#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminlist.h"
#include "listclass.h"
#include <QMessageBox>

extern AdminList AL;
extern ListClass LC;
string KINDS[4] = {"Teacher", "Student", "Temp", "Other"};
extern string GetTime();
extern long long CASHID;

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


void MainWindow::on_actionchongzhi_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->chongzhi_ui);
}


void MainWindow::on_pushButton_6_clicked()
{
    LC.Charge(ui->cardNum->text().toStdString(), ui->chargeMoney->currentText().toStdString(), ui->cardKinds->currentIndex()+4);
}

void MainWindow::on_actionyuechakan_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->yue_ui);
}


void MainWindow::on_pushButton_7_clicked()
{
    LC.resetPtr();
    stringstream ss;
    ss << LC.find(ui->lineEdit->text().toStdString(), 0);
    string str[9];
    for (int i = 0;ss >> str[i] && i < 9 ; ++i) {

    }
    ui->textBrowser_9->setText(QString::fromStdString(str[4]));
    ui->textBrowser_10->setText(QString::fromStdString(str[5]));
    ss.clear();
}


void MainWindow::on_pushButton_8_clicked()
{
    if(!AL.verify(AL.getUser(), ui->lineEdit_5->text().toStdString())) {
        QMessageBox::warning(this, "警告！", "密码错误！", QMessageBox::Yes);
        ui->lineEdit_5->clear();
    } else {
        CASHID++;
        string str = ui->lineEdit_2->text().toStdString() + " " + std::to_string(CASHID) + " " +
                GetTime() + " " + ui->lineEdit_3->text().toStdString() + " " +
                ui->lineEdit_4->text().toStdString() + " " + AL.getUser();
        LC.Use(str, ui->comboBox->currentIndex()+4);
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
    }
}


void MainWindow::on_actionshiyong_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->shiyong_ui);
}


void MainWindow::on_actionchangepwd_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->changepwd_ui);
}


void MainWindow::on_pushButton_9_clicked()
{
    string aPwd = ui->lineEdit_6->text().toStdString();
    string bPwd1 = ui->lineEdit_7->text().toStdString();
    string bPwd2 = ui->lineEdit_8->text().toStdString();
    if (bPwd1 != bPwd2) {
        QMessageBox::warning(this, "警告！", "密码咋还能不一样啊？", QMessageBox::Yes);
    } else {
        AL.change(aPwd, bPwd1);
    }
}


void MainWindow::on_pushButton_10_clicked()
{
    if (ui->comboBox_2->currentIndex() == 1) {
        if (QMessageBox::Yes == QMessageBox::warning(this, "警告！", "您即将永远失去您可爱的账号！", QMessageBox::Yes | QMessageBox::No)) {
            LC.Change(ui->lineEdit_9->text().toStdString(), ui->lineEdit_10->text().toStdString(), ui->comboBox_2->currentIndex()+6, std::to_string(1));
            ui->lineEdit_9->clear();
            ui->lineEdit_10->clear();
        } else {

        }
    } else {
        if (QMessageBox::Yes == QMessageBox::warning(this, "警告！", "您即将挂失您可爱的账号！不过不要担心，该操作是可逆的！", QMessageBox::Yes | QMessageBox::No)) {
            LC.Change(ui->lineEdit_9->text().toStdString(), ui->lineEdit_10->text().toStdString(), ui->comboBox_2->currentIndex()+6, std::to_string(1));
            ui->lineEdit_9->clear();
            ui->lineEdit_10->clear();
        } else {

        }
    }
}


void MainWindow::on_actionguashi_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->guashi_ui);
}


void MainWindow::on_pushButton_11_clicked()
{
        if (QMessageBox::Yes == QMessageBox::information(this, "注意！", "是否将该卡解除挂失", QMessageBox::Yes | QMessageBox::No)) {
            LC.Change(ui->lineEdit_11->text().toStdString(), ui->lineEdit_12->text().toStdString(), 6 , std::to_string(0));
            ui->lineEdit_11->setFocus();
            ui->lineEdit_11->clear();
            ui->lineEdit_12->clear();
        } else {
            ui->lineEdit_11->setFocus();
        }
}


void MainWindow::on_actionjiegua_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->jiegua_ui);
}

