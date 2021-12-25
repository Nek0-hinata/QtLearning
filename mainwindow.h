#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlQuery>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_actionsearching_triggered();

    void on_actiontongji_triggered();

    void on_actionluru_triggered();

    void on_actionzhuce_triggered();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_actionchongzhi_triggered();

    void on_pushButton_6_clicked();

    void on_actionyuechakan_triggered();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_actionshiyong_triggered();

    void on_actionchangepwd_triggered();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_actionguashi_triggered();

    void on_pushButton_11_clicked();

    void on_actionjiegua_triggered();

    void on_searchingBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    QSqlQuery q;
};
#endif // MAINWINDOW_H
