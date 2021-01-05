#ifndef CHECKINGSTRING_H
#define CHECKINGSTRING_H

#include <QString>

class CheckingString
{
public:
   static bool CheckingTheString(QString enterString);
};

#endif // CHECKINGSTRING_H

//проверка строки на то, число это или нет
bool CheckingString::CheckingTheString(QString enterString)
{
    int num=0;
    bool flagNum;
    num = enterString.toInt(&flagNum, 10);  //возвращается 0, если введенная строка не число
    if (num==0) {
        return false;
    } else return true;
}
