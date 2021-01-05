#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QDialog>
#include "QtSql"
#include "QSqlDatabase"
#include "QSqlQuery"

namespace Ui {
class Organization;
}

class Organization : public QDialog
{
    Q_OBJECT

public:
    explicit Organization(QWidget *parent = nullptr, int type_organization=0);
    ~Organization();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_registration_clicked();

private:
    Ui::Organization *ui;
    int type_org;

    //функция для передачи значений о типе организаций между окнами
    void InitValueOrganization();
};

#endif // ORGANIZATION_H
