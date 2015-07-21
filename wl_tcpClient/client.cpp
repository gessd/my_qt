#include <QMessageBox>
#include <QString>

#include "client.h"
#include "ui_client.h"

//#include <QTableWidgetItem>

client::client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);

    ui->clientSendpushButton->setEnabled (false);
    ui->disconnectpushButton->setEnabled (false);
    tcp=NULL;
    message=tr("<span style=\"color:red\">%1</span>");
}

client::~client()
{
    delete tcp;
    delete ui;
}


//客户端发送信息
void client::clientSendMessage ()
{
    QByteArray data;
    data.append(ui->messagetextEdit->toPlainText());     //
    tcp->write(data);       //写入数据
    ui->messagetextBrowser->insertPlainText (tr("send message: %1 \n").arg (QString(data)));
}

//清空按钮
void client::on_cCleanpushButton_clicked()
{
    ui->messagetextBrowser->setText ("");   //清空数据
}

//客户端连接按钮槽函数
void client::on_connectpushButton_clicked()
{
    serverIP = ui->clientIPlineEdit->text ();
    clientPort = ui->clientPortlineEdit->text ();
    if(serverIP.isEmpty () || clientPort.isEmpty ())    //判断IP端口是否有数据
    {
        QMessageBox::warning (this, tr("Warnning"), tr("服务器IP或端口号不能为空"));
        return;
    }

    if(tcp)     //如果当前tcp已有连接，则释放当前连接
    {
        delete tcp;
    }
    tcp=new QTcpSocket(this);
    tcp->connectToHost (serverIP, clientPort.toInt()); //连接到主机
    connect (tcp, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect (tcp, SIGNAL(connected()), this, SLOT(updateClientStatusConnect())); //更新连接状态
    //connect (tcp, SIGNAL(disconnected()), this, SLOT(updateClientStatusDisonnect())); //更新断开连接状态
    connect(tcp,SIGNAL(readyRead()),this,SLOT(readMessage()));
    ui->connectpushButton->setEnabled (false);
    ui->disconnectpushButton->setEnabled (true);
}

//断开连接按钮
void client::on_disconnectpushButton_clicked()
{
    ui->messagetextEdit->setText (tr("clientStop"));
    clientSendMessage ();
    ui->messagetextEdit->setText (tr(""));
    ui->cStatuslabel->setText (tr("连接断开"));
    tcp->abort();
    delete tcp;
    tcp=NULL;
    ui->connectpushButton->setEnabled (true);
    ui->disconnectpushButton->setEnabled (false);
    ui->clientSendpushButton->setEnabled (false);

    int iLen = ui->userTableWidget->rowCount();
    for(int i=0; i<iLen; i++)
    {
        ui->userTableWidget->removeRow(i);
    }
}

//客户端错误提示
void client::displayError (QAbstractSocket::SocketError)
{
      QMessageBox::warning (this, tr("Warnning"), tcp->errorString ());
      tcp->close ();
      ui->connectpushButton->setEnabled (true);
      ui->disconnectpushButton->setEnabled (false);
      ui->clientSendpushButton->setEnabled (false);
}

//更新连接状态
void client::updateClientStatusConnect ()
{
    ui->cStatuslabel->setText (tr("已连接"));
    ui->connectpushButton->setEnabled (false);
    ui->disconnectpushButton->setEnabled (true);
    ui->clientSendpushButton->setEnabled (true);
}

//void client::updateClientStatusDisonnect()
//{
//    ui->cStatuslabel->setText (tr("服务器停止侦听"));
//    ui->connectpushButton->setEnabled (true);
//    ui->disconnectpushButton->setEnabled (false);
//    ui->clientSendpushButton->setEnabled (false);
//}

//需要自己添加的函数
void client::updateStatus()
{
    ui->connectpushButton->setEnabled (false);
    ui->disconnectpushButton->setEnabled (true);
    ui->clientSendpushButton->setEnabled (true);
}

//客户端读取信息
void client::readMessage ()
{
//    QByteArray data=tcp->readAll();

//    message = QString(data);
//    if(message.contains ("serverStop")) //如果收到是客户端断开连接的信息
//    {
//        ui->cStatuslabel->setText (tr("服务器停止侦听"));
//        ui->connectpushButton->setEnabled (true);
//        ui->disconnectpushButton->setEnabled (false);
//        ui->clientSendpushButton->setEnabled (false);
//       return;
//    }
    int type;
    QString uIP, message;
    QDataStream in(tcp);
    in.setVersion(QDataStream::Qt_4_6);
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    in >> type >> uIP;
    QTableWidgetItem *ip = new QTableWidgetItem(uIP);
    switch(type)
    {
    case Message:
        in >> message;
        ui->messagetextBrowser->append(time +uIP +message);
        break;
    case NewParticipant:
        ui->messagetextBrowser->append(time +uIP +tr("接入"));
        ui->userTableWidget->insertRow(0);
        ui->userTableWidget->setItem(0, 0, ip);
        break;
    case ParticipantLeft:
        int rowNum = ui->userTableWidget->findItems(uIP, Qt::MatchExactly).first()->row();
        ui->userTableWidget->removeRow(rowNum);
        ui->messagetextBrowser->setTextColor(Qt::red);
        ui->messagetextBrowser->append(time +uIP +tr("离开"));
        break;
    }
//    ui->messagetextBrowser->append(message.arg(tr("&lt;&lt;收到消息:"))+QString(data));
}

//发送按钮
void client::on_clientSendpushButton_clicked()
{
    QByteArray data;
    data.append(ui->messagetextEdit->toPlainText());
    tcp->write(data);
    ui->messagetextBrowser->insertPlainText (tr("send message: %1 \n").arg (QString(data)));
    ui->messagetextEdit->clear();
    ui->messagetextEdit->setFocus();
}
