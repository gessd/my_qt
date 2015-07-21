#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QNetworkInterface>
#include <QtNetwork>


namespace Ui {
    class client;
}

// 枚举变量标志信息的类型，分别为消息，新用户加入，用户退出，文件名，拒绝接受文件
enum MessageType{Message, NewParticipant, ParticipantLeft, FileName, Refuse};

class client : public QDialog
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = 0);
    ~client();

private:
    Ui::client *ui;

    QString clientPort;
    QString serverIP;
    QString message;
    QTcpSocket *tcp;

private slots:
    void clientSendMessage();
    void updateStatus();
    void readMessage();  //接收数据
    void displayError(QAbstractSocket::SocketError);  //显示客户端错误
    void on_connectpushButton_clicked();
    void on_cCleanpushButton_clicked();
    void updateClientStatusConnect();
//    void updateClientStatusDisonnect();
    void on_disconnectpushButton_clicked();
    void on_clientSendpushButton_clicked();
};

#endif // CLIENT_H
