#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlQuery>
class QTcpServer;
class QTcpSocket;
class QStandardItemModel;

namespace Ui {
class Dialog;
}

enum MessageType{LoginUser, RegisterUser, Message, NewParticipant, ParticipantLeft, FileName, Refuse, TempMessage};
enum UserLogin{LoginT, RegisterT};

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    QStandardItemModel *model;
    ~Dialog();
    
private:
    Ui::Dialog *ui;
    QTcpServer *tcpServer;
    QList<QTcpSocket *>mytcpsocket;
    QSqlQuery query;
    QString sqlpant;
    void info_init();
    bool sqlOpen(QString pathstr);

private slots:
    void updateStatus();
    void serverReadMessage();
    void updateSendStatus();
    void on_startBtn_clicked();
    void on_stopBtn_clicked();
};

#endif // DIALOG_H
