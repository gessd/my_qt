#include "tskpage.h"
#include "QMessageBox"
tskpage::tskpage(QObject *parent) :
    QObject(parent)
{

}

void tskpage::startexamm()
{
    QMessageBox::about(0,"1","startexam");
}

void tskpage::startoneexam(QString msg)
{
    QMessageBox::about(0,"1",msg);
}

QString tskpage::starttowexam(QString msg)
{
    return msg+"abc";
}
