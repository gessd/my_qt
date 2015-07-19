#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    info_init();
}
Dialog::~Dialog()
{
    delete ui;
}
void Dialog::info_init()//信息初始化，主要是获取本地IP
{
    QList<QHostAddress>address=QNetworkInterface::allAddresses();
    foreach(QHostAddress add,address)
    {
        if(add.protocol()==QAbstractSocket::IPv4Protocol)
        {
             ui->comboBox->addItem(add.toString());
        }
    }
    ui->portlineEdit->setText("6666");
    QString strTcpInfo="";
    QList<QNetworkInterface>list = QNetworkInterface::allInterfaces();
    //获取所有网络接口的列表
    foreach(QNetworkInterface interface,list)
    {
        //遍历每一个网络接口
        //qDebug() <<"Device:"<<interface.name();
        strTcpInfo+="Device:"+interface.name()+"\n";
        //设备名
        //qDebug() <<"HardwareAddress: "<<interface.hardwareAddress();
        strTcpInfo+="HardwareAddress: "+interface.hardwareAddress()+"\n";
        //硬件地址
        QList<QNetworkAddressEntry>entryList = interface.addressEntries();
        //获取IP地址条目列表，每个条目中包含一个IP地址，一个子网掩码和一个广播地址
        foreach(QNetworkAddressEntry entry,entryList)
        {
            if(entry.ip().protocol()==QAbstractSocket::IPv4Protocol && entry.ip().toString()!="127.0.0.1")
            {
                //遍历每一个IP地址条目
                //qDebug()<<"IP Address: "<<entry.ip().toString();
                strTcpInfo+="IP Address: "+entry.ip().toString()+"\n";
                //IP地址
                //qDebug()<<"Netmask: "<<entry.netmask().toString();
                strTcpInfo+="Netmask: "+entry.netmask().toString()+"\n";
                //子网掩码
                //qDebug()<<"Broadcast: "<<entry.broadcast().toString();
                strTcpInfo+="Broadcast: "+entry.broadcast().toString()+"\n";
                //广播地址
            }
        }
    }
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString strTime = time.toString("yyyy-MM-dd\nhh:mm:ss"); //设置显示格式
    strTime="System Time:\n"+strTime;
    ui->timelabel->setText(strTime);//在标签上显示时间
    ui->textBrowser->setAlignment( Qt::AlignCenter );
    ui->textBrowser->setText(strTcpInfo);
    //pushButton按钮初始化
    ui->stoppushButton->setEnabled(false);
    ui->startpushButton->setEnabled(true);
    //treeWidget初始化
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->setHeaderLabels(QStringList()<<"User IP"<<"Client Port"<<"UID"<<"Recive Message");
    ui->treeWidget->header()->setResizeMode(QHeaderView::ResizeToContents);
    ui->treeWidget->header()->setStretchLastSection(true);
}

void Dialog::on_startpushButton_clicked()//开始（Start）按钮单击，开启服务
{
    tcpServer=new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress(ui->comboBox->currentText()),ui->portlineEdit->text().toInt()))
    {
        //QMessageBox::warning (this, tr("Warnning"), tcpServer->errorString ());
        QString error="listening failed: "+tcpServer->errorString();
        ui->statuslabel->setText(error);
        return;
    }
    ui->stoppushButton->setEnabled(true);
    ui->startpushButton->setEnabled(false);
    QString strTmp="IP:"+ui->comboBox->currentText()+" is listening...";
    ui->statuslabel->setText(strTmp);
    connect (tcpServer, SIGNAL(newConnection()),this, SLOT(updateStatus()));//有新客户连接
}

void Dialog::updateStatus()//有客户来连接了
{
    QTcpSocket *clientConnection=tcpServer->nextPendingConnection ();//获取socket
    QString clientInfo="User "+clientConnection->peerAddress().toString()+"连接成功";
    ui->messagetextEdit->setText(clientInfo);
    //qDebug()<<"peerAddress: "<<clientConnection->peerAddress()<<" peerName: "<<clientConnection->peerName()<<" peerPort: "<<clientConnection->peerPort();
    QStringList columItemList;
    QTreeWidgetItem *A;
    columItemList<<clientConnection->peerAddress().toString()<<QString::number(clientConnection->peerPort())<<QString::number(clientConnection->socketDescriptor());
    A = new QTreeWidgetItem(columItemList);
    ui->treeWidget->addTopLevelItem(A);
    mytcpsocket.append(clientConnection);
    connect (clientConnection, SIGNAL(disconnected()), this, SLOT(updateSendStatus()));
    connect (clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
    connect (clientConnection, SIGNAL(readyRead()), this, SLOT(serverReadMessage()));
}

void Dialog::serverReadMessage()//接受客户发送的信息
{
    for(int i=0;i<mytcpsocket.length();i++)
    {
        //qDebug()<<"bytesAvailable"<<mytcpsocket[i]->bytesAvailable()<<"    ";
        if(mytcpsocket[i]->bytesAvailable()>0)
        {
            QByteArray datarcv=mytcpsocket[i]->readAll();
            QString clientmsg(datarcv);
            QList<QTreeWidgetItem *>treelist=ui->treeWidget->findItems(QString::number(mytcpsocket[i]->socketDescriptor()),Qt::MatchExactly,2);
            //ui->treeWidget->removeItemWidget(treelist[0],3);
            QStringList columItemList;
            QTreeWidgetItem *A;
            columItemList<<mytcpsocket[i]->peerAddress().toString()<<QString::number(mytcpsocket[i]->peerPort())<<QString::number(mytcpsocket[i]->socketDescriptor())<<clientmsg;
            A = new QTreeWidgetItem(columItemList);
            int index=ui->treeWidget->indexOfTopLevelItem(treelist[0]);
            ui->treeWidget->takeTopLevelItem(index);
            //Removes the top-level item at the given index in the tree and returns it, otherwise returns 0;
            ui->treeWidget->insertTopLevelItem(index,A);
            clientmsg="hi "+clientmsg+"\n";
            QByteArray datasend;
            datasend.append(clientmsg);
            mytcpsocket[i]->write(datasend);

        }
        //qDebug()<<mytcpsocket[i]->socketDescriptor();//<<mytcpsocket[i]->SocketState;
    }
}

void Dialog::updateSendStatus()//客户断开连接
{
    for(int i=0;i<mytcpsocket.length();i++)
    {
        //qDebug()<<"bytesAvailable"<<mytcpsocket[i]->bytesAvailable()<<"    ";
        if(mytcpsocket[i]->state()==QAbstractSocket::UnconnectedState)
        {
            //qDebug()<<mytcpsocket[i]->peerAddress()<<" is disconnected!";
            QList<QTreeWidgetItem *>treelist=ui->treeWidget->findItems(QString::number(mytcpsocket[i]->peerPort()),Qt::MatchExactly,1);
            int index=ui->treeWidget->indexOfTopLevelItem(treelist[0]);
            ui->treeWidget->takeTopLevelItem(index);
            ui->statuslabel->setText(mytcpsocket[i]->peerAddress().toString()+" is disconnected!");
            mytcpsocket.removeAt(i);
        }
        //qDebug()<<mytcpsocket[i]->isReadable()<<mytcpsocket[i]->peerPort()<<mytcpsocket[i]->socketDescriptor()<<mytcpsocket[i]->state();
    }
}


void Dialog::on_stoppushButton_clicked()//停止按钮单击
{
    tcpServer->close();
    ui->treeWidget->clear();
    mytcpsocket.clear();
    ui->stoppushButton->setEnabled(false);
    ui->startpushButton->setEnabled(true);
    ui->statuslabel->setText("Server is Stopped");
}
