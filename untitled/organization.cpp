#include <QString>
#include <QMessageBox>
#include <QDate>

#include "organization.h"
#include "ui_organization.h"
#include "log.h"
#include "checkingstring.h"

Organization::Organization(QWidget *parent, int type_organization) :
    QDialog(parent),
    ui(new Ui::Organization)
{
    ui->setupUi(this);
    type_org=type_organization;
    InitValueOrganization();
}

Organization::~Organization()
{
    delete ui;
}

//передача значений о типе организаций между окнами
void Organization::InitValueOrganization() {
    switch(type_org)
    {
    case 0:
        ui->type_organization->setText("Контролирующий орган");
        Log::SaveLog("Регистрация следующего типа организации - ", "Контролирующий орган");    //запись лога
        //отключаются поля, которые не нужно заполнять
        ui->type_lic_med->setEnabled(false);
        ui->type_lic_farm->setEnabled(false);
        ui->license_date->setEnabled(false);
        ui->license_number->setEnabled(false);
        ui->license_organization->setEnabled(false);
        break ;
    case 1:
        ui->type_organization->setText("Госучреждение с медицинской лицензией");
        Log::SaveLog("Регистрация следующего типа организации - ", "Госучреждение с медицинской лицензией");    //запись лога
        break ;
    case 2:
        ui->type_organization->setText("Госучреждение с фармацевтической лицензией");
        Log::SaveLog("Регистрация следующего типа организации - ", "Госучреждение с фармацевтической лицензией");    //запись лога
        break ;
    case 3:
        ui->type_organization->setText("ООО с медицинской лицензией");
        Log::SaveLog("Регистрация следующего типа организации - ", "ООО с медицинской лицензией");    //запись лога
        break ;
    case 4:
        ui->type_organization->setText("ООО с фармацевтической лицензией");
        Log::SaveLog("Регистрация следующего типа организации - ", "ООО с фармацевтической лицензией");    //запись лога
        break ;
    case 5:
        ui->type_organization->setText("ИП с медицинской лицензией");
        Log::SaveLog("Регистрация следующего типа организации - ", "ИП с медицинской лицензией");    //запись лога
        break ;
    case 6:
        ui->type_organization->setText("ИП с фармацевтической лицензией");
        Log::SaveLog("Регистрация следующего типа организации - ", "ИП с фармацевтической лицензией");    //запись лога
        break ;
    case 7:
        ui->type_organization->setText("Смешанная лицензия");
        Log::SaveLog("Регистрация следующего типа организации - ", "Смешанная лицензия");    //запись лога
        break ;
    }

}
//отмена регистрации
void Organization::on_pushButton_cancel_clicked()
{
    Organization::close();
}

//регистрация организации в базе данных
void Organization::on_pushButton_registration_clicked()
{
    QString name=ui->name->text();
    QString inn=ui->inn->text();
    QString address=ui->address->text();
    QString telephone=ui->telephone->text();
    QString director=ui->director->text();
    QString licenseType;
    //проверка нажатия флажков (одного или нескольких)
    if (ui->type_lic_med->isChecked()&&ui->type_lic_farm->checkState() == Qt::Unchecked)
        {
            licenseType="1";
        } else if (ui->type_lic_med->checkState() == Qt::Unchecked&&ui->type_lic_farm->isChecked())
        {
            licenseType="2";
        } else if (ui->type_lic_med->isChecked()&&ui->type_lic_farm->isChecked())
        {
            licenseType="3";
        }
    QString licenseNumber=ui->license_number->text();
    //не получается установить текущую дату
    QDate licenseDate;
    ui->license_date->setDate(licenseDate);
    ////////////////////////////////
    QString licenseOrganization=ui->license_organization->text();
    QString typeOrganization = QString::number(type_org);
    //проверка ввода ИНН (количество символов)
    bool flagInn=true;
    if (type_org==1||type_org==2||type_org==3||type_org==4||type_org==7){
        if (inn.size()!=10) {
            ui->checking_data->setText("Некорректный ИНН");
            flagInn=false;
        }
    } else if (type_org==5||type_org==6) {
        if (inn.size()!=12) {
            ui->checking_data->setText("Некорректный ИНН");
            flagInn=false;
        }
    }

    //проверка того, что ИНН - это число (не работает корректно)
    bool flaInnNum=true;
    /*if (!(CheckingString::CheckingTheString(inn))) {
        ui->checking_data->setText("3-Некорректный ИНН");
        flaInnNum=false;
    }*/
    //проверка регистрации организации с имеющимся ИНН
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Programing\\ExtractRecipes\\Data.sqlite");
    db.open();
    bool flagInn1=true;
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT inn FROM table_organization WHERE inn LIKE '"+ inn +"'");
    db.close();
    while (query.next()) {
        //получаем данные о имеющейся почте в базе данных и сравниваем ее с введенной
    auto tempInn  = query.value(0).toString();
    if (tempInn==inn) {
        QMessageBox::critical(this, "Ошибка","Организация с таким ИНН уже зарегистрирована");
        flagInn1=false;
    }
    }
    //проверка заполнения таблицы
    bool flagData1=true, flagData2=true;
    if (type_org==0) {     //проверка заполнения таблицы если тип пользователя - контролирующий орган
        if (name.size()==0||inn.size()==0||address.size()==0||telephone.size()==0||
            director.size()==0) {
        ui->checking_data->setText("Проверьте заполнение данных");
        flagData1=false;
        }
    } else { //если иная организация, то добавляются поля с лицензией
        if (name.size()==0||inn.size()==0||address.size()==0||telephone.size()==0||director.size()==0||licenseType.size()==0
                ||licenseType.size()==0||licenseNumber.size()==0||licenseOrganization.size()==0) {
         ui->checking_data->setText("Проверьте заполнение данных");
         flagData2=false;
        }
    }
    //добавление данных в таблицу если проверка инн прошла корректно и все поля заполнены
        if (flagInn && flaInnNum && flagInn1 && flagData1 && flagData2) {
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Programing\\ExtractRecipes\\Data.sqlite");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    if (query.exec("INSERT INTO table_organization (name, inn, address, telephone, director, license_type, license_number, license_date, license_organization, type_organization) "
               "VALUES('"+name+"', '"+inn+"', '"+address+"', '"+telephone+"', '"+director+"', '"+licenseType+"', '"+licenseNumber+"', '"+licenseDate.toString()+"', '"+licenseOrganization+"', '"+typeOrganization+"')"))
    {
        QMessageBox::information(this, "Результат","Организация "+ name + " добавлена");
        Log::SaveLog("Результат - ","Организация "+ name + " добавлена, ", "ИНН - " + inn);    //запись лога
        QDialog::close();
    } else {
        QMessageBox::information(this, "Результат","Организация "+ name + " НЕ добавлена");
    }
    db.close();
        }
}
