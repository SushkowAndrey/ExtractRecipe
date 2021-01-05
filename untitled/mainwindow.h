#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtSql"
#include "QSqlDatabase"
#include "QSqlQuery"
#include <QString>

//форма для связывания окон
#include "account.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //указатель на будущую форму
private:
    account *Account;

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_enter_clicked();

    void on_pushButton_registration_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
