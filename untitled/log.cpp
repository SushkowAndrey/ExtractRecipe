#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDate>
#include <QTime>

#include "log.h"

void Log::SaveLog(QString textOne)
{
    QDate cdate = QDate::currentDate(); // возвращаем текущую дату
    QTime ctime = QTime::currentTime(); // возвращаем текущее время

    QFile fileLog("log.txt");
    if (fileLog.open(QIODevice::Append)) {
        QTextStream outFile(&fileLog);
        outFile <<cdate.toString() + " "+ ctime.toString()+ " - " + textOne << Qt::endl;
    } else {
       // ui->statusbar->showMessage("Поля очищены");
    }
}

void Log:: SaveLog(QString textOne, QString textTwo)
{
     QDate cdate = QDate::currentDate(); // возвращаем текущую дату
     QTime ctime = QTime::currentTime(); // возвращаем текущее время

     QFile fileLog("log.txt");
     if (fileLog.open(QIODevice::Append)) {
         QTextStream outFile(&fileLog);
         outFile <<cdate.toString() + " "+ ctime.toString()+ " - " + textOne + " "+ textTwo << Qt::endl;
     } else {
        // ui->statusbar->showMessage("Поля очищены");
     }
}

void Log:: SaveLog(QString textOne, QString textTwo, QString textThree)
{
    QDate cdate = QDate::currentDate(); // возвращаем текущую дату
    QTime ctime = QTime::currentTime(); // возвращаем текущее время

    QFile fileLog("log.txt");
    if (fileLog.open(QIODevice::Append)) {
        QTextStream outFile(&fileLog);
        outFile <<cdate.toString() + " "+ ctime.toString()+ " - " + textOne + " "+ textTwo + " "+ textThree<< Qt::endl;
    } else {
       // ui->statusbar->showMessage("Поля очищены");
    }
}
