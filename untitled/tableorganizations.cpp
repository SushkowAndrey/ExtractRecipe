#include "tableorganizations.h"

TableOrganizations::TableOrganizations(){}

TableOrganizations::TableOrganizations(int num, QString name, QString inn)
{
    this->num = num;
    this->name = name;
    this->inn = inn;
}
