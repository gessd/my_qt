#include "userland.h"
#include "ui_userland.h"

#include <QTcpSocket>
#include <QMessageBox>

UserLand::UserLand(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLand)
{
    ui->setupUi(this);
    tcp = NULL;
    serverIP = "192.168.0.127";
    clientPort = "6666";
}

UserLand::~UserLand()
{
    delete ui;
}

void UserLand::on_loginBtn_clicked()
{
    mType = LoginUser;
    tcp = new QTcpSocket(this);
    tcp->connectToHost(serverIP, clientPort.toInt());
    connect (tcp, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcp,SIGNAL(readyRead()),this,SLOT(readMessage()));
    sendMessage();
//    accept();
}

void UserLand::on_registerBtn_clicked()
{
    mType = RegisterUser;
}

//连接错误提示
void UserLand::displayError (QAbstractSocket::SocketError)
{
      QMessageBox::warning (this, tr("Warnning"), tcp->errorString ());
      tcp->close ();
}

void UserLand::sendMessage()
{
    QByteArray byArr;
    QDataStream outData(&byArr, QIODevice::WriteOnly);
    outData.setVersion(QDataStream::Qt_4_6);
    int uid = ui->lineEdit->text().toInt();
    QString uname = ui->lineEdit_2->text();

    switch (mType) {
    case LoginUser:
        outData << mType << uid;
        tcp->write(byArr);
        break;

    case RegisterUser:
        outData << mType << uname;
        tcp->write(byArr);
        break;
    }
}

void UserLand::readMessage()
{
    int uType;
    QByteArray bArr;
    QDataStream inData(&bArr, QIODevice::ReadOnly);
    inData.setVersion(QDataStream::Qt_4_6);
    inData >> uType;
    switch(uType)
    {
    case LoginT:
        //qDebug()<<"login true";
        tcp->close();
        accept();
        break;
    case RegisterT:
        tcp->close();
        accept();
        break;
    }
}
