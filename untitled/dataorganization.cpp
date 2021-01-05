#include "dataorganization.h"
#include "ui_dataorganization.h"

DataOrganization::DataOrganization(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::DataOrganization)
{
    ui->setupUi(this);
    idOrganization=id;
    InputDataOrganization();
}

DataOrganization::~DataOrganization()
{
    delete ui;
}

void DataOrganization::on_pushButton_clicked()
{
    DataOrganization::close();
}

//информация об организации в окне описания
void DataOrganization::InputDataOrganization()
{
    QString name;
    QString inn;
    QString address;
    QString telephone;
    QString director;
    QString type_organization;
    QString license_type;
    QString license_number;
    QDate license_date;
    QString license_organization;
    //запрос из базы данных
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Programing\\ExtractRecipes\\Data.sqlite");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT  name, inn, address, telephone, director, type_organization, license_type, license_number, license_date, license_organization"
               " FROM table_organization WHERE id = " + QString::number(idOrganization));
    //Выводим значения из запроса
    while (query.next())
    {
    name = query.value(0).toString();
    inn = query.value(1).toString();
    address = query.value(2).toString();
    telephone = query.value(3).toString();
    director = query.value(4).toString();
    type_organization= query.value(5).toString();
    license_type= query.value(6).toString();
    license_number= query.value(7).toString();
    license_date= query.value(8).toDate();
    license_organization= query.value(9).toString();
    }
    db.close();
    ui->name->setText(name);
    ui->inn->setText(inn);
    ui->address->setText(address);
    ui->telephone->setText(telephone);
    ui->director->setText(director);
    switch(type_organization.toInt())
    {
    case 0:
        ui->type_organization->setText("Контролирующий орган");
        break ;
    case 1:
        ui->type_organization->setText("Госучреждение с медицинской лицензией");
        if (license_type=="1") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская"); }
        if (license_type=="2") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Фармацевтическая"); }
        if (license_type=="3") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская и фармацевтическая"); }
        ui->number->setText("Номер лицензии"); ui->number_license->setText(license_number);
        ui->data->setText("Дата лицензии"); ui->data_license->setText(license_date.toString());
        ui->number->setText("Организация, выдавшая лицензии"); ui->number_license->setText(license_organization);
        break ;
    case 2:
        ui->type_organization->setText("Госучреждение с фармацевтической лицензией");
        if (license_type=="1") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская"); }
        if (license_type=="2") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Фармацевтическая"); }
        if (license_type=="3") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская и фармацевтическая"); }
        ui->number->setText("Номер лицензии"); ui->number_license->setText(license_number);
        ui->data->setText("Дата лицензии"); ui->data_license->setText(license_date.toString());
        ui->number->setText("Организация, выдавшая лицензии"); ui->number_license->setText(license_organization);
        break ;
    case 3:
        ui->type_organization->setText("ООО с медицинской лицензией");
        if (license_type=="1") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская"); }
        if (license_type=="2") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Фармацевтическая"); }
        if (license_type=="3") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская и фармацевтическая"); }
        ui->number->setText("Номер лицензии"); ui->number_license->setText(license_number);
        ui->data->setText("Дата лицензии"); ui->data_license->setText(license_date.toString());
        ui->number->setText("Организация, выдавшая лицензии"); ui->number_license->setText(license_organization);
        break ;
    case 4:
        ui->type_organization->setText("ООО с фармацевтической лицензией");
        if (license_type=="1") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская"); }
        if (license_type=="2") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Фармацевтическая"); }
        if (license_type=="3") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская и фармацевтическая"); }
        ui->number->setText("Номер лицензии"); ui->number_license->setText(license_number);
        ui->data->setText("Дата лицензии"); ui->data_license->setText(license_date.toString());
        ui->number->setText("Организация, выдавшая лицензии"); ui->number_license->setText(license_organization);
        break ;
    case 5:
        ui->type_organization->setText("ИП с медицинской лицензией");
        if (license_type=="1") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская"); }
        if (license_type=="2") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Фармацевтическая"); }
        if (license_type=="3") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская и фармацевтическая"); }
        ui->number->setText("Номер лицензии"); ui->number_license->setText(license_number);
        ui->data->setText("Дата лицензии"); ui->data_license->setText(license_date.toString());
        ui->number->setText("Организация, выдавшая лицензии"); ui->number_license->setText(license_organization);
        break ;
    case 6:
        ui->type_organization->setText("ИП с фармацевтической лицензией");
        if (license_type=="1") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская"); }
        if (license_type=="2") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Фармацевтическая"); }
        if (license_type=="3") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская и фармацевтическая"); }
        ui->number->setText("Номер лицензии"); ui->number_license->setText(license_number);
        ui->data->setText("Дата лицензии"); ui->data_license->setText(license_date.toString());
        ui->number->setText("Организация, выдавшая лицензии"); ui->number_license->setText(license_organization);
        break ;
    case 7:
        ui->type_organization->setText("Смешанная лицензия");
        if (license_type=="1") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская"); }
        if (license_type=="2") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Фармацевтическая"); }
        if (license_type=="3") { ui->type->setText("Тип лицензии"); ui->type_license->setText("Медицинская и фармацевтическая"); }
        ui->number->setText("Номер лицензии"); ui->number_license->setText(license_number);
        ui->data->setText("Дата лицензии"); ui->data_license->setText(license_date.toString());
        ui->number->setText("Организация, выдавшая лицензии"); ui->number_license->setText(license_organization);
        break ;
    }



}
