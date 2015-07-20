#include <QtGui/QApplication>
#include "client.h"

#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//添加中文支持2-2
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    Widget w;
//    w.show();
    client w1;
    w1.show();

    return a.exec();
}
