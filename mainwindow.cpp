#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminlist.h"
#include "listclass.h"
#include <QMessageBox>
#include <database.h>

extern AdminList AL;
extern ListClass LC;
string KINDS[4] = {"Teacher", "Student", "Temp", "Other"};

extern string GetTime();

extern long long CASHID;
extern bool isMysql;
extern DataBase DB;

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

//注册管理员
void MainWindow::on_pushButton_3_clicked() {
    if (isMysql) {
        if (ui->password1->text() != ui->password2->text()) {
            QMessageBox::warning(this, "warning", "The two passwords are inconsistent", QMessageBox::Yes);
        } else {
            DB.addAdmin(ui->userName->text(), ui->password1->text());
        }
        ui->userName->clear();
        ui->password1->clear();
        ui->password2->clear();
        ui->userName->setFocus();
    } else {
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
}

//删除管理员
void MainWindow::on_pushButton_4_clicked() {
    if (isMysql) {
        if (ui->userName->text() == QString::fromStdString("admin")) {
            QMessageBox::critical(this, "警告警告警告", "您可不能删除这个用户啊", QMessageBox::Yes);
        }
        if (ui->password1->text() != ui->password2->text()) {
            QMessageBox::warning(this, "啊？？", "咋两次密码还能不一样呢？", QMessageBox::Yes);
        } else {
            DB.deleteAdmin(ui->userName->text(), ui->password1->text());
        }
        ui->userName->clear();
        ui->password1->clear();
        ui->password2->clear();
        ui->userName->setFocus();
    } else {
        if (ui->password1->text() != ui->password2->text()) {
            QMessageBox::warning(this, "啊？？", "咋两次密码还能不一样呢？", QMessageBox::Yes);
        } else {
            AL.del(ui->userName->text().toStdString(), ui->password1->text().toStdString());
        }
        ui->userName->clear();
        ui->password1->clear();
        ui->password2->clear();
        ui->userName->setFocus();
    }
}

//添加卡片信息
void MainWindow::on_pushButton_2_clicked() {
    if (isMysql) {
        DB.addCard(ui->kinds->currentText(), ui->name->text(), ui->company->text());
    } else {
        string I = KINDS[ui->kinds->currentIndex()] + " " + ui->name->text().toStdString() + " " +
                   ui->company->text().toStdString();
        LC.input(I);
        ui->name->clear();
        ui->company->clear();
    }
}

//查询
void MainWindow::on_pushButton_clicked() {
    if (isMysql) {
        ui->pushButton->setText("查找");
        ui->pushButton_5->setText("下一个");
        QString str;
        QString searchStr = ui->searchLine->text();
        switch (ui->searchingBox->currentIndex()) {
            case 0:
                str = QString::fromStdString("user_id");
                ui->textBrowser->setText(searchStr);
                break;
            case 1:
                str = QString::fromStdString("user_kinds");
                ui->searchLine->setPlaceholderText("请输入种类：教工卡/学生卡/临时卡/其他卡");
                ui->textBrowser_2->setText(searchStr);
                break;
            case 2:
                str = QString::fromStdString("user_name");
                ui->textBrowser_3->setText(searchStr);
                break;
            case 3:
                str = QString::fromStdString("user_company");
                ui->textBrowser_4->setText(searchStr);
                break;
            case 4:
                str = QString::fromStdString("user_incash");
                ui->textBrowser_5->setText(searchStr);
                break;
            case 5:
                str = QString::fromStdString("user_outcash");
                ui->textBrowser_6->setText(searchStr);
                break;
            case 6:
                str = QString::fromStdString("user_loss");
                ui->textBrowser_7->setText(searchStr);
                break;
        }
        q = DB.find(ui->searchLine->text(), str);
        if (q.next()) {
            ui->textBrowser->setText(q.value(0).toString());
            ui->textBrowser_2->setText(q.value(1).toString());
            ui->textBrowser_3->setText(q.value(2).toString());
            ui->textBrowser_4->setText(q.value(3).toString());
            ui->textBrowser_5->setText(q.value(4).toString());
            ui->textBrowser_6->setText(q.value(5).toString());
            ui->textBrowser_7->setText(q.value(6).toString());
            ui->textBrowser_8->setText("否");
        } else {
            QMessageBox::warning(this, "哦呀", "找不到该用户! 或许已经被注销了？", QMessageBox::Yes);
            ui->textBrowser->clear();
            ui->textBrowser_2->clear();
            ui->textBrowser_3->clear();
            ui->textBrowser_4->clear();
            ui->textBrowser_5->clear();
            ui->textBrowser_6->clear();
            ui->textBrowser_7->clear();
            switch (ui->searchingBox->currentIndex()) {
                case 0:
                    ui->textBrowser->setText(searchStr);
                    break;
                case 1:
                    ui->textBrowser_2->setText(searchStr);
                    break;
                case 2:
                    ui->textBrowser_3->setText(searchStr);
                    break;
                case 3:
                    ui->textBrowser_4->setText(searchStr);
                    break;
                case 4:
                    ui->textBrowser_5->setText(searchStr);
                    break;
                case 5:
                    ui->textBrowser_6->setText(searchStr);
                    break;
                case 6:
                    ui->textBrowser_7->setText(searchStr);
                    break;
            }
            ui->textBrowser_8->setText("有可能");
        }

    } else {
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
}


void MainWindow::on_pushButton_5_clicked() {
    if (isMysql) {
        if (q.next()) {
            ui->textBrowser->setText(q.value(0).toString());
            ui->textBrowser_2->setText(q.value(1).toString());
            ui->textBrowser_3->setText(q.value(2).toString());
            ui->textBrowser_4->setText(q.value(3).toString());
            ui->textBrowser_5->setText(q.value(4).toString());
            ui->textBrowser_6->setText(q.value(5).toString());
            ui->textBrowser_7->setText(q.value(6).toString());
            ui->textBrowser_8->setText("否");
        } else {
            QMessageBox::warning(this, "哦呀", "找不到该用户! 或许已经被注销了？", QMessageBox::Yes);
            ui->textBrowser->clear();
            ui->textBrowser_2->clear();
            ui->textBrowser_3->clear();
            ui->textBrowser_4->clear();
            ui->textBrowser_5->clear();
            ui->textBrowser_6->clear();
            ui->textBrowser_7->clear();
            ui->textBrowser_8->setText("有可能");
        }
    } else {
        LC.resetPtr();
        QMessageBox::information(this, "震惊", "你已经把锚点重置了！");
    }
}


void MainWindow::on_actionchongzhi_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->chongzhi_ui);
}

//充值
void MainWindow::on_pushButton_6_clicked() {
    if (isMysql) {
        if (DB.legal(ui->cardNum->text())) {
            DB.charge(ui->cardNum->text(), ui->chargeMoney->currentText(), ui->cardKinds->currentText());
        } else {
            QMessageBox::critical(this, "真让人惊讶", "您的账号已挂失");
        }
    } else {
        LC.Charge(ui->cardNum->text().toStdString(), ui->chargeMoney->currentText().toStdString(),
                  ui->cardKinds->currentIndex() + 4);
    }
}

void MainWindow::on_actionyuechakan_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->yue_ui);
}

//余额查询
void MainWindow::on_pushButton_7_clicked() {
    if (isMysql) {
        QSqlQuery que = DB.find(ui->lineEdit->text(), QString::fromStdString("user_id"));
        if (que.next()) {
            ui->textBrowser_9->setText(que.value(5).toString());
            ui->textBrowser_10->setText(que.value(4).toString());
        } else {
            QMessageBox::warning(this, "啊呀", "您的小可爱失踪了");
        }
    } else {
        LC.resetPtr();
        stringstream ss;
        ss << LC.find(ui->lineEdit->text().toStdString(), 0);
        string str[9];
        for (int i = 0; ss >> str[i] && i < 9; ++i) {

        }
        ui->textBrowser_9->setText(QString::fromStdString(str[4]));
        ui->textBrowser_10->setText(QString::fromStdString(str[5]));
        ss.clear();
    }
    ui->textBrowser_9->clear();
    ui->textBrowser_10->clear();
}

//消费
void MainWindow::on_pushButton_8_clicked() {
    if (isMysql) {
        if (DB.verify(DB.ReturnUser(), ui->lineEdit_5->text())) {
            DB.consume(ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit_4->text(),
                       ui->comboBox->currentIndex());
        } else {
            QMessageBox::warning(this, "啊呀", "密码不对啊亲");
        }
    } else {
        if (!AL.verify(AL.getUser(), ui->lineEdit_5->text().toStdString())) {
            QMessageBox::warning(this, "警告！", "密码错误！", QMessageBox::Yes);
            ui->lineEdit_5->clear();
        } else {
            CASHID++;
            string str = ui->lineEdit_2->text().toStdString() + " " + std::to_string(CASHID) + " " +
                         GetTime() + " " + ui->lineEdit_3->text().toStdString() + " " +
                         ui->lineEdit_4->text().toStdString() + " " + AL.getUser();
            LC.Use(str, ui->comboBox->currentIndex() + 4);

        }
    }
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}


void MainWindow::on_actionshiyong_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->shiyong_ui);
}


void MainWindow::on_actionchangepwd_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->changepwd_ui);
}

//更改当前密码
void MainWindow::on_pushButton_9_clicked() {
    if (isMysql) {
        QString aPwd = ui->lineEdit_6->text();
        QString bPwd1 = ui->lineEdit_7->text();
        QString bPwd2 = ui->lineEdit_8->text();
        if (bPwd1 != bPwd2) {
            QMessageBox::warning(this, "警告！", "密码咋还能不一样啊？", QMessageBox::Yes);
        } else {
            if (DB.verify(DB.ReturnUser(), aPwd)) {
                DB.changePwd(bPwd1);
                QMessageBox::information(this, "哦天啊", "下次要记得密码！");
            } else {
                QMessageBox::critical(this, "卧槽", "你也记不住密码？");
            }
        }
    } else {
        string aPwd = ui->lineEdit_6->text().toStdString();
        string bPwd1 = ui->lineEdit_7->text().toStdString();
        string bPwd2 = ui->lineEdit_8->text().toStdString();
        if (bPwd1 != bPwd2) {
            QMessageBox::warning(this, "警告！", "密码咋还能不一样啊？", QMessageBox::Yes);
        } else {
            AL.change(aPwd, bPwd1);
        }
    }
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_6->setFocus();
}

//挂失与注销
void MainWindow::on_pushButton_10_clicked() {
    if (isMysql) {
        if (ui->comboBox_2->currentIndex() == 0) {
            DB.changeLoss(ui->lineEdit_9->text(), ui->lineEdit_10->text(), 0);
        } else {
            DB.deleteCard(ui->lineEdit_9->text(), ui->lineEdit_10->text());
        }
    } else {
        if (ui->comboBox_2->currentIndex() == 1) {
            if (QMessageBox::Yes ==
                QMessageBox::warning(this, "警告！", "您即将永远失去您可爱的账号！", QMessageBox::Yes | QMessageBox::No)) {
                LC.Change(ui->lineEdit_9->text().toStdString(), ui->lineEdit_10->text().toStdString(),
                          ui->comboBox_2->currentIndex() + 6, std::to_string(1));
            }
        } else {
            if (QMessageBox::Yes ==
                QMessageBox::warning(this, "警告！", "您即将挂失您可爱的账号！不过不要担心，该操作是可逆的！", QMessageBox::Yes | QMessageBox::No)) {
                LC.Change(ui->lineEdit_9->text().toStdString(), ui->lineEdit_10->text().toStdString(),
                          ui->comboBox_2->currentIndex() + 6, std::to_string(1));
            }
        }
    }
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
}


void MainWindow::on_actionguashi_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->guashi_ui);
}

//解挂
void MainWindow::on_pushButton_11_clicked() {
    if (isMysql) {

    } else {
        if (QMessageBox::Yes ==
            QMessageBox::information(this, "注意！", "是否将该卡解除挂失", QMessageBox::Yes | QMessageBox::No)) {
            LC.Change(ui->lineEdit_11->text().toStdString(), ui->lineEdit_12->text().toStdString(), 6,
                      std::to_string(0));
            ui->lineEdit_11->setFocus();
            ui->lineEdit_11->clear();
            ui->lineEdit_12->clear();
        } else {
            ui->lineEdit_11->setFocus();
        }
    }
}


void MainWindow::on_actionjiegua_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->jiegua_ui);
}


void MainWindow::on_searchingBox_currentIndexChanged(int index) {
    if (index == 1) {
        ui->searchLine->setPlaceholderText("请输入种类：教工卡/学生卡/临时卡/其他卡");
    } else {
        ui->searchLine->setPlaceholderText("请输入查询内容");
    }
}

