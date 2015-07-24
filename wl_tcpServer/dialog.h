#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QNetworkInterface>
#include <QDateTime>
#include <QStringList>
#include <QHostInfo>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Dialog;
}

// 枚举变量标志信息的类型，分别为消息，新用户加入，用户退出，文件名，拒绝接受文件
enum MessageType{Message, NewParticipant, ParticipantLeft, FileName, Refuse, TempMessage};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
    void on_startpushButton_clicked();
    void updateStatus();
    void serverReadMessage();
    void updateSendStatus();
    void on_stoppushButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    QTcpServer *tcpServer;
    QList<QTcpSocket *>mytcpsocket;//连接成功的套接字
    void info_init();//信息初始化
    void messageTransmit(QString uIP, QString message, int socketDescriptor);
};

#endif // DIALOG_H
