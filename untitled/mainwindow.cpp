#include <QString>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registration.h"
#include "account.h"
#include "log.h"
#include "passwordrecovery.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Log::SaveLog("Запуск программы");    //запись лога
}

MainWindow::~MainWindow()
{
    Log::SaveLog("Выход из программы");    //запись лога
    delete ui;
}

//очистка полей ввода
void MainWindow::on_pushButton_clear_clicked()
{
    ui->input_email->clear();
    ui->input_password->clear();
    Log::SaveLog("Очистка данных");    //запись лога
}

//кнопка для авторизации
void MainWindow::on_pushButton_enter_clicked()
{
    //ввод логина и пароля
    QString login=ui->input_email->text();
    QString password=ui->input_password->text();
    Log::SaveLog("Попытка аутентификации пользователя с логином", login);    //запись лога
    //модель базы данных
    DBConnect db;
    AccountModel accountModel=db.SelectAccountModel(login, password);
    if (accountModel.id>0) {
        Log::SaveLog("Вход пользователя в личный кабинет - ", login);    //запись лога
        //MainWindow::close();
        Account = new account (this, accountModel.id);
        Account->exec();
    } else {
        ui->label_invalid_data->setText("Неверные идентификационные данные или пользователь неактивен");
        Log::SaveLog("Неверные идентификационные данные или пользователь неактивен");    //запись лога
    }
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

//восстановление пароля
void MainWindow::on_pushButton_password_recovery_clicked()
{
    Log::SaveLog("Восстановление пользователя");    //запись лога
    ui->input_email->clear();
    ui->input_password->clear();
    PasswordRecovery passwordRecovery;
    passwordRecovery.exec();

}
