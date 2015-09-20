#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    w.dlog;
    w.dlog->exec();

    //w.show();
    return a.exec();
}
