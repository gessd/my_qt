#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QSqlQuery>
class sqlQuery
{
public:
    bool sqlOpen(QString path);
    QSqlQuery queryexec(QString sqlstr);
};

#endif // SQLQUERY_H
