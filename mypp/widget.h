#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHostInfo>

namespace Ui {
class Widget;
}

// 枚举变量标志信息的类型，分别为消息，新用户加入，用户退出，文件名，拒绝接受文件
enum MessageType
{
    Message,
    NewParticipant,
    ParticipantLeft,
    FileName,
    Refuse
};
class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    QString text();
    ~Widget();
    
private slots:
    void on_sendButton_clicked();

    void on_exitButton_clicked();

    void on_pushButton_clicked();

    void processPendingDatagrams();

    void lookedup(const QHostInfo &host);  //other

private:
    Ui::Widget *ui;

    QUdpSocket *udpSocket;
    qint16 port;

protected:
    QString getUserName();
    QString getHostName();
    QString getIp();

    void newUser(QString userName, QStirng localHostName, QString ipAddress);
    void userList(QString userName, QStirng localHostName, QString ipAddress);
    void sendMessage(MessageType type, QString serverAddress="");

    QString temp;   //other
};

#endif // WIDGET_H
