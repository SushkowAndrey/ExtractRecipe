#include <QString>

#include "account.h"
#include "ui_account.h"
#include "mainwindow.h"
#include "log.h"


account::account(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::account)
{
    ui->setupUi(this);
    idAccount=id;
    InitValue();
}

account::~account()
{
    Log::SaveLog("Выход из личного кабинета");    //запись лога
    delete ui;
}

void account::InitValue()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Programing\\ExtractRecipes\\Data.sqlite");
    db.open();
    //Осуществляем запрос
    QString sql = QStringLiteral("SELECT lastName, name, middleName, position, email, type_user FROM table_person WHERE id = %1;").arg(idAccount);
    QSqlQuery query;
    query.exec(sql);
    //Выводим значения из запроса
    db.close();
    while (query.next()) {
        auto lastName = query.value(0).toString();
        auto name = query.value(1).toString();
        auto middleName = query.value(2).toString();
        auto position = query.value(3).toString();
        auto email = query.value(4).toString();
        auto typeUser = query.value(5).toString();

        ui->lastName->setText(lastName);
        ui->name->setText(name);
        ui->middleName->setText(middleName);
        ui->position->setText(position);
        ui->email->setText(email);
        if (typeUser=="1")
        {
            ui->type_user->setText("Администратор");
        } else if (typeUser=="2") {
            ui->type_user->setText("Пользователь");
        }
    }
}

//закрытие окна без сохранения данных
void account::on_pushButton_exit_clicked()
{

    this->close();
    //MainWindow MainWindow_user;
    //MainWindo

}
