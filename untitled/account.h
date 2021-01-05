#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDialog>
#include "QtSql"
#include "QSqlDatabase"
#include "QSqlQuery"

namespace Ui {
class account;
}

class account : public QDialog
{
    Q_OBJECT

public:
    explicit account(QWidget *parent = nullptr, int id=0);
    ~account();

private slots:
    void on_pushButton_exit_clicked();

private:
    Ui::account *ui;
    int idAccount;
    //заполнение аккаунта
    void InitValue();
};

#endif // ACCOUNT_H
