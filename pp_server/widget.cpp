#include "widget.h"
#include "ui_widget.h"

#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QByteArray>
#include <QDataStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::Any, 1666))
    {
        QMessageBox::warning(this, tr("err"), tr("listen err"));
        close();
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::waitMessage(userType type, QString Ip, QString User, QDataStream inMessage)
{
    QByteArray arr;
    switch(type)
    {
    case newUser:
        break;

    case leaveUser:
        break;
    }
}
