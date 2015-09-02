#include "widget.h"
#include "dialog.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    Dialog dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        Widget w;
        w.uid = dlg.nui;
        w.uname = dlg.ustr;
        w.global();
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
