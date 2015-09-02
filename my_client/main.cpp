#include "dialog.h"
#include "userland.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    UserLand userLandDlg;
    if(userLandDlg.exec() == QDialog::Accepted)
    {
        Dialog w;
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }

}
