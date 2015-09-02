/*
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
*/

#include <QtCore/QCoreApplication>
#include <qmap.h>
#include <qdebug.h>

#include <string.h>

int main(int argc, char *argv[])
{
/*
    QCoreApplication a(argc, argv);

    QMap<QString,int> map;
    map.insert("eins o",1);
    map.insert("sieben",7);
    map["a test"]=23;
    //Normally, a QMap allows only one value per key.
    //If you call insert() with a key that already exists in the QMap,
    //the previous value will be erased
    map["a test"]=13;

    int val=map.value("a test");
    qDebug()<<val;

    int val2=map.value("error");
    qDebug()<<val2;    ///0

    int val3=map.value("error2",20);
    qDebug()<<val3;

    int val4=map.value("a test",40);
    qDebug()<<val4;
    ////using a java-style iterator
    QMapIterator<QString,int> iter(map);
    while(iter.hasNext())
    {
        iter.next();  ///放在前面
        qDebug()<<iter.key()<<" "<<iter.value();
    }
    ////using an Stl-style iterator
    QMap<QString,int>::ConstIterator i=map.constBegin();
    while(i!=map.constEnd())
    {
        qDebug()<<i.key()<<": "<<i.value();
        ++i;
    }

    QMap<QString,int>::Iterator it;
    it=map.find("sieben");
    if(it!=map.end())
        it.value()=8;

    for(QMap<QString,int>::ConstIterator ite=map.constBegin(); ite!=map.constEnd(); ++ite)
        qDebug()<<ite.key()<<": "<<ite.value();

    return 0;//a.exec();
*/

    char string[20];
    char *ptr;
    char c='r';
    strcpy(string,"There are two rings");
    ptr=strrchr(string,c);
    //ptr=strchr(string,c);
    if (ptr!=NULL)
    {
        printf("The character %c is at position:%s\n",c,ptr);
    }
    else
    {
        printf("The character was not found\n");
    }
    return 0;
}
