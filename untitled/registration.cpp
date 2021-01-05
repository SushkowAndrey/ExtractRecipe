#include <QString>
#include <QMessageBox>

#include "registration.h"
#include "ui_registration.h"
#include "log.h"
#include "selectingorganization.h"
#include "dataorganization.h"

registration::registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
    InputTableOrganization(CountOrganization());
}

registration::~registration()
{
    delete ui;
}

int registration::CountOrganization()
{

    //запрос из базы данных
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Programing\\ExtractRecipes\\Data.sqlite");
    db.open();
    //Осуществляем запрос для подсчета количества строк
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM table_organization WHERE active=1");
    db.close();
    if (query.next()) return query.value(0).toInt();
    else return 0;
}


void registration::InputTableOrganization(int countOrganization)
{
    //подготовка к заполнению
    //установка количества строк
    ui->table_organization->setRowCount(countOrganization);
    //установка количества столбцов
    ui->table_organization->setColumnCount(3);
    //названия колонок
    ui->table_organization->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Номер")));
    ui->table_organization->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Наименование организации")));
    ui->table_organization->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("      ИНН      ")));
    //изменить размер по содержимому
    ui->table_organization->resizeColumnsToContents();
    //разрешена сортировка
    ui->table_organization->setSortingEnabled(true);
    //запрет редактирования данных
    ui->table_organization->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //запрос базы данных из таблицы
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Programing\\ExtractRecipes\\Data.sqlite");
    db.open();
    //Осуществляем запрос заполнения таблицы
    QSqlQuery query;
    query.exec("SELECT id, name, inn FROM table_organization WHERE active=1");
    while(query.next())
    {
        ui->table_organization->insertRow(0);
        ui->table_organization->setItem(0, 0,new QTableWidgetItem(query.value(0).toString()));
        ui->table_organization->setItem(0, 1,new QTableWidgetItem(query.value(1).toString()));
        ui->table_organization->setItem(0, 2,new QTableWidgetItem(query.value(2).toString()));
    }
    db.close();

   /* //удалить пустые ячейки - не работает
    for(int j=0; j < CountOrganization(); j++)
    {
        bool flag = ui->table_organization->item(j,0)->text().isNull();

        if (!flag) //ячейки пустые
        {

        }
        else
        {
            continue;
        }
    }*/
}

//закрытие окна без сохранения данных
void registration::on_pushButton_cancel_clicked()
{
    QDialog::close();
}

//очистка полей для ввода
void registration::on_pushButton_clear_clicked()
{
    ui->input_lastName->clear();
    ui->input_name->clear();
    ui->input_middleName->clear();
    ui->input_position->clear();
    ui->input_email->clear();
    ui->input_password->clear();
    ui->input_password_repeate->clear();
}

//регистрация пользователя
void registration::on_pushButton_registration_clicked()
{
    QString lastName=ui->input_lastName->text();
    QString name=ui->input_name->text();
    QString middleName=ui->input_middleName->text();
    QString position=ui->input_position->text();
    QString email=ui->input_email->text();
    QString password=ui->input_password->text();
    QString passwordRepeate=ui->input_password_repeate->text();
    QString typeUser;
    //tableOrganizationId="1";//временная переменная

    if (ui->type_user_Admin->isChecked())
        {
            typeUser="1";
        } else if (ui->type_user_User->isChecked())
        {
            typeUser="2";
        }
    bool flagData=true;
    bool flagPasswordRepeate=true;
    //проверка заполнения таблицы
    if (lastName.size()==0||name.size()==0||middleName.size()==0||position.size()==0||
            email.size()==0||password.size()==0||passwordRepeate.size()==0||typeUser.size()==0) {
        ui->cheking_strings->setText("Проверьте заполнение данных");
        flagData=false;
    }
    bool flagDataOrganization=true;
    if (tableOrganizationId.size()==0) {
        ui->cheking_strings->setText("Выберите организацию");
        flagDataOrganization=false;
    }
    //проверка регистрации пользователя с имеющимся email
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Programing\\ExtractRecipes\\Data.sqlite");
    db.open();
    bool flagEmail=true;
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT email FROM table_person WHERE email LIKE '"+ email +"'");
    db.close();
    while (query.next()) {
        //получаем данные о имеющейся почте в базе данных и сравниваем ее с введенной
    auto emailTemp  = query.value(0).toString();
    if (emailTemp==email) {
        QMessageBox::critical(this, "Ошибка","Такой пользователь уже зарегистрирован");
        flagEmail=false;
    }
    }
    //проверка если разный пароль
    if (password!=passwordRepeate) {
        ui->cheking_strings->setText("Выбранные пароли не совпадают");
        flagPasswordRepeate=false;
    }
    //добавление данных в таблицу если проверки повторного ввода пароля пройдены и поля заполнены
    if (flagData&&flagEmail&&flagPasswordRepeate&&flagDataOrganization) {
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Programing\\ExtractRecipes\\Data.sqlite");
    db.open();
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("INSERT INTO table_person (lastName, name, middleName, position, email, password, type_user, table_organization_id) "
               "VALUES ('" + lastName + "', '" + name + "', '" + middleName + "','" + position + "','"
                + email + "','" + password + "','" + typeUser + "','"+ tableOrganizationId + "')");
    Log::SaveLog("Пользователь с логином - ", email, " зарегистрирован");    //запись лога
    QMessageBox::information(this, "Результат","Успешная регистрация");
    QDialog::close();
    db.close();
    }
}

//добавление новой организации
void registration::on_pushButton_add_clicked()
{
    Log::SaveLog("Добавление новой организации");    //запись лога
    SelectingOrganization selectingorganization;
    selectingorganization.exec();
}

//обновить список организаций
void registration::on_pushButton_update_clicked()
{
    ui->table_organization->clearContents();
    //запрос базы данных из таблицы
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Programing\\ExtractRecipes\\Data.sqlite");
    db.open();
    //Осуществляем запрос для подсчета количества строк
    QSqlQuery query;
    query.exec("SELECT id, name, inn FROM table_organization WHERE active=1");
    while(query.next())
    {
        ui->table_organization->insertRow(0);
        ui->table_organization->setItem(0, 0,new QTableWidgetItem(query.value(0).toString()));
        ui->table_organization->setItem(0, 1,new QTableWidgetItem(query.value(1).toString()));
        ui->table_organization->setItem(0, 2,new QTableWidgetItem(query.value(2).toString()));
    }
    db.close();
}

//открывать данные об организации двойным кликом
void registration::on_table_organization_itemDoubleClicked(QTableWidgetItem *item)
{
    //определяем ячейку с номером организации (первая колонка с выбранной строкой)
    item=ui->table_organization->item(ui->table_organization->currentRow(), 0);
    //передаем ее номер далее в окно для просмотра сведений об организации
    int numRowOrganization=(item->text()).toInt();
    dataOrganization = new DataOrganization (this, numRowOrganization);
    dataOrganization->exec();
}

//выбор конкретной организации для пользователя
void registration::on_table_organization_itemClicked(QTableWidgetItem *item)
{
    item=ui->table_organization->item(ui->table_organization->currentRow(), 0);
    tableOrganizationId=item->text();
    //показ данной организации на экране
    item=ui->table_organization->item(ui->table_organization->currentRow(), 1);
    ui->selection_organization->setText(item->text());
}
