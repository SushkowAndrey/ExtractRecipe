#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QTableWidgetItem>
#include "QtSql"
#include "QSqlDatabase"
#include "QSqlQuery"

//форма для связывания окон
#include "dataorganization.h"

namespace Ui {
class registration;
}

class registration : public QDialog
{
    Q_OBJECT

public:
    explicit registration(QWidget *parent = nullptr);
    ~registration();
private:
        //указатель на будущую форму
    DataOrganization * dataOrganization;

private slots:

    void on_pushButton_cancel_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_registration_clicked();

    void on_pushButton_update_clicked();

    void on_table_organization_itemDoubleClicked(QTableWidgetItem *item);

    void on_table_organization_itemClicked(QTableWidgetItem *item);

private:
    Ui::registration *ui;
    //количество зарегистрированных организаций
    int CountOrganization();
    //функция для заполнения таблицы с организациями при регистрации пользователя
    void InputTableOrganization(int countOrganization);
    //номер организации для конкретного пользователя
    QString tableOrganizationId;

};

#endif // REGISTRATION_H
