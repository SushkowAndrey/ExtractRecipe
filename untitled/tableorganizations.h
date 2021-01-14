#ifndef TABLEORGANIZATIONS_H
#define TABLEORGANIZATIONS_H

#include <QString>

//класс организации для добавления в таблицу TableWidget
class TableOrganizations
{
public:
public:
    int num;
    QString name;
    QString inn;
    TableOrganizations();
    TableOrganizations(int num, QString name, QString inn);
};

#endif // TABLEORGANIZATIONS_H
