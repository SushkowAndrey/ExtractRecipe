#include <QString>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registration.h"
#include "account.h"
#include "log.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Log::SaveLog("Запуск программы");    //запись лога
}

MainWindow::~MainWindow()
{
    delete ui;
}

//очистка полей ввода
void MainWindow::on_pushButton_clear_clicked()
{
    ui->input_email->clear();
    ui->input_password->clear();
}

//кнопка для авторизации
void MainWindow::on_pushButton_enter_clicked()
{
    //ввод логина и пароля
    QString login=ui->input_email->text();
    QString password=ui->input_password->text();
    Log::SaveLog("Попытка аутентификации пользователя с логином", login);    //запись лога
    //сверка логина и пароля с базой данных
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Programing\\ExtractRecipes\\Data.sqlite");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT id FROM table_person WHERE email='" + login + "'AND password='" + password + "'AND active=1");
    if (query.next()) {
        Log::SaveLog("Вход пользователя в личный кабинет - ", login);    //запись лога
        int idAccount= query.value(0).toInt();
        MainWindow::close();
        Account = new account (this, idAccount);
        Account->exec();
    } else {
        ui->label_invalid_data->setText("Неверные идентификационные данные или пользователь неактивен");
        Log::SaveLog("Неверные идентификационные данные или пользователь неактивен");    //запись лога
    }
    db.close();
}
//открытие окна для регистрации
void MainWindow::on_pushButton_registration_clicked()
{
    Log::SaveLog("Регистрация нового пользователя");    //запись лога
    ui->input_email->clear();
    ui->input_password->clear();
    registration registration_user;
    registration_user.exec();
}
