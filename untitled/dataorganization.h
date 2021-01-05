#ifndef DATAORGANIZATION_H
#define DATAORGANIZATION_H

#include <QDialog>
#include "QtSql"
#include "QSqlDatabase"
#include "QSqlQuery"
#include <QString>

namespace Ui {
class DataOrganization;
}

class DataOrganization : public QDialog
{
    Q_OBJECT

public:
    explicit DataOrganization(QWidget *parent = nullptr, int id=0);
    ~DataOrganization();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DataOrganization *ui;
    int idOrganization;
    void InputDataOrganization();
};

#endif // DATAORGANIZATION_H
