#ifndef LOG_H
#define LOG_H
#include <QString>


class Log
{
public:
    static void SaveLog(QString textOne);
    static void SaveLog(QString textOne, QString textTwo);
    static void SaveLog(QString textOne, QString textTwo, QString textThree);
};

#endif // LOG_H
