#include "widget.h"
#include "ui_widget.h"

#include <QHostInfo>
#include <QProcess>
#include <QUdpSocket>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>

#include <QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //QHostInfo::lookupHost("www.baidu.com", this, SLOT(lookedup(QHostInfo)));  //获取网络地址

    udpSocket = new QUdpSocket(this);
    port = 55555;
    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    sendMessage(NewParticipant);
}

Widget::~Widget()
{
    delete ui;
}

//发送按钮
void Widget::on_sendButton_clicked()
{
    sendMessage(Message);
}

//退出按钮
void Widget::on_exitButton_clicked()
{
    close();
}

//获取用户名
QString Widget::getUserName()
{
    QStringList envVariables;
    envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*"
                 << "HOSTNAME.*" << "DOMAINNAME.*";
    QStringList environment = QProcess::systemEnvironment();
        //QProcess::systemEnvironment()系统环境变量
    foreach (QString string, envVariables)  //有序迭代容器中的所有项
    {
        int index = environment.indexOf(QRegExp(string));
                //QRegExp正则表达式；indexOf查找QStringList特定字符串返回索引
        if (index != -1)
        {
            QStringList stringList = environment.at(index).split('=');
                //at索引，从0开始；split('='),以=分割字符串；
            if (stringList.size() == 2)
            {
                return stringList.at(1);
                break;
            }
        }
    }
    return "unknown";
}

//获取主机名
QString Widget::getHostName()
{
    QString hostName = QHostInfo::localHostName();      //获取计算机名
    return hostName;
}

//获取IP
QString Widget::getIp()
{
    QHostInfo info = QHostInfo::fromName(getHostName());    //根据主机名获取IP地址
    //qDebug() << info.addresses();
    foreach(QHostAddress address, info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return tr("getIP_err");
}

QString Widget::getMessage()
{
    return tr("null");
}

//新用户加入
void Widget::newUser(QString userName, QString localHostName, QString ipAddress)
{
    bool isEmpty = ui->tableWidget->findItems(localHostName, Qt::MatchExactly).isEmpty();
    if(isEmpty)
    {
        QTableWidgetItem *user = new QTableWidgetItem(userName);
        QTableWidgetItem *host = new QTableWidgetItem(localHostName);
        QTableWidgetItem *ip = new QTableWidgetItem(ipAddress);

        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0, 0, user);
        ui->tableWidget->setItem(0, 1, host);
        ui->tableWidget->setItem(0, 2, ip);
        ui->messageBrowser->setTextColor(Qt::gray);
        ui->messageBrowser->setCurrentFont(QFont("Times New Roman",10));
        //arg为返回后面文本的一个副本,%1表示输出的内容按照第1个.arg后面的输出？
        ui->messageBrowser->append(tr("%1 在线！").arg(userName));

        sendMessage(NewParticipant);
    }
}

//用户列表
void Widget::userList(QString userName, QString localHostName, QString ipAddress)
{
}

//自定义函数
void Widget::text()
{
/*=============QStringList操作==============
    QString str = "1,2,3,4,5,6,7,8,9";
    QStringList strList;
    strList = str.split(",");   //分割字符串，以,为界分割str后存入strList
    qDebug() << strList;        //分割后字符串输出形式("1", "2", "3", "4", "5", "6", "7", "8", "9")
    qDebug() << strList.size();
    for(int i = 0; i < strList.size(); i++)
        qDebug() << i + 1 << ":" << strList[i];
    QString str2;
    str2 = strList.join(",");   //与split互逆，以,为界合并字符
    qDebug() << str2;
*/

/*==============文件读写===================
    QFile f("c:\\test.txt");
    if(!f.open(QIODevice::WriteOnly))
    {
        qDebug() << "Open failed.";
    }

    QTextStream txtOutput(&f);
    QString s1(tr("123"));
    quint32 n1(123);

    txtOutput << s1 << endl;
    txtOutput << n1 << endl;

    f.close();
*/

    QByteArray arr;
    arr.resize(10);
    qDebug() << arr;
}

//自定义按钮函数
void Widget::on_pushButton_clicked()
{
    //getUserName();
    //qDebug() << temp;
    //text();
    QFile f("c:\\test.txt");
    if(!f.open(QIODevice::WriteOnly))
    {
        qDebug() << "Open failed.";
    }
    QString userName, localName, ipAddress, message;
    QTextStream txtInput(&f);
    txtInput >> userName >> localName >> ipAddress >> message;
    qDebug() << userName;
    qDebug() << localName;
    qDebug() << ipAddress;
    qDebug() << message;
    f.close();
}

//自定义槽函数
void Widget::lookedup(const QHostInfo &host)        //对应槽函数
{
    qDebug()<<host.addresses().first().toString();//输出了第一个 ip地址
}

//发送消息
void Widget::sendMessage(MessageType type, QString serverAddress)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    QString localHostName = getHostName();
    QString address = getIp();
    out << type << getUserName() << localHostName;

    switch (type)
    {
    case Message:
        if(ui->messagetextEdit->toPlainText() == "")    //toPlainText获取文本
        {
            QMessageBox::warning(this, tr("err"), tr("null err"), QMessageBox::Ok);
            return;
        }
        out << address << getMessage();
        ui->messageBrowser->verticalScrollBar()
                ->setValue(ui->messageBrowser->verticalScrollBar()->maximum());
        break;

    case NewParticipant:
        out << address;
        break;
    case ParticipantLeft :
        break;

    case FileName :
        break;

    case Refuse :
        break;
    }
    udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
}

//接受消息
void Widget::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());  //resize重新定义数组的大小
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);
        int messageType;
        in >> messageType;
        QString userName, localHostName, ipAddress, message;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        switch(messageType)
        {
        case Message:
            in >> userName >> localHostName >> ipAddress >> message;
            //qDebug() << messageType << userName << localHostName << ipAddress << message;
            ui->messageBrowser->setTextColor(Qt::blue);
            ui->messageBrowser->setCurrentFont(QFont("Times New Roman",12));
            ui->messageBrowser->append("[" + localHostName + "]" + time);
            ui->messageBrowser->append(message);
            break;

        case NewParticipant:
            in >> userName >> localHostName >> ipAddress;
            newUser(userName, localHostName, ipAddress);
            break;

        case ParticipantLeft:
            in >> userName >> localHostName >> ipAddress;
            userList(userName, localHostName, ipAddress);
            break;

        case FileName:
            break;

        case Refuse:
            break;
        }
    }
}
