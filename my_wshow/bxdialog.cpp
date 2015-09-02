#include "bxdialog.h"
#include "ui_bxdialog.h"
#include "QMouseEvent"
#include "windows.h"

bxDialog::bxDialog(QWidget *parent) :
    QDialog(parent),
    bdialog(new Ui::bxDialog)
{
    bdialog->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    bdialog->groupBox_total->installEventFilter(this);
}

bxDialog::~bxDialog()
{
    delete bdialog;
}

bool bxDialog::eventFilter(QObject *o, QEvent *e)
{
    const int frameWidth=0;
    const int captionHeight=30;
    int w=this->width();
    int h=this->height();
    if( e->type()==QMouseEvent::MouseButtonPress)
    {
        QMouseEvent * mouse=(QMouseEvent*)e;
        if (QRect(frameWidth, frameWidth, w-frameWidth-frameWidth, captionHeight-frameWidth).contains(mouse->x(),mouse->y())) //标题
        {
            ReleaseCapture();
            ::SendMessage(this->winId(),WM_NCLBUTTONDOWN, HTCAPTION, 0);//MAKELPARAM(mouse->x(), mouse->y()));
            return true;
        }
        return false;
    }
}
