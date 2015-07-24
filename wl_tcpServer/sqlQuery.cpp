#include "sqlQuery.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQueryModel>

bool sqlQuery::sqlOpen(QString path)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("path");
    return db.open();
}

QSqlQuery sqlQuery::queryexec(QString sqlstr)
{

}



