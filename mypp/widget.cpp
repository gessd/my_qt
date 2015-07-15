#include "widget.h"
#include "ui_widget.h"

#include <QHostInfo>
#include <QProcess>
#include <QUdpSocket>

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

//新用户加入
void Widget::newUser(QString userName, QString localHostName, QString ipAddress)
{
}

//用户列表
void Widget::userList(QString userName, QString localHostName, QString ipAddress)
{
}

//临时函数
QString Widget::text()
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
    return temp;
}

//调试使用函数
void Widget::on_pushButton_clicked()
{
    //getUserName();
    //qDebug() << temp;
    getUserName();
}

//调试使用函数
void Widget::lookedup(const QHostInfo &host)        //对应槽函数
{
    qDebug()<<host.addresses().first().toString();//输出了第一个 ip地址
}

//发送消息
void Widget::sendMessage(MessageType type, QString serverAddress)
{

}

//接受消息
void Widget::processPendingDatagrams()
{
}
