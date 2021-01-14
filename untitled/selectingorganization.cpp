#include "ui_selectingorganization.h"
#include "selectingorganization.h"

SelectingOrganization::SelectingOrganization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectingOrganization)
{
    ui->setupUi(this);
}

SelectingOrganization::~SelectingOrganization()
{
    delete ui;
}

void SelectingOrganization::on_pushButton_cancel_clicked()
{
    QDialog::close();
}

//передача данных из окна с выбором типа пользователя
void SelectingOrganization::on_pushButton_further_clicked()
{
    int typeOrganization=ui->type_organization->currentIndex();
    if (typeOrganization==-1) {
        ui->warning->setText("Выберите тип организации");
    } else {
    SelectingOrganization::close();
    organization = new Organization (this, typeOrganization);
    QDialog::close();
    organization->exec();
    }
}
