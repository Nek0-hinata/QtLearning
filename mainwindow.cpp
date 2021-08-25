#include "mainwindow.h"
#include "ui_mainwindow.h"

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

