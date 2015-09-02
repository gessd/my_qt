#ifndef USERLAND_H
#define USERLAND_H

#include <QDialog>
#include <QAbstractSocket>
class QTcpSocket;

enum MessageType{LoginUser, RegisterUser, Message, NewParticipant, ParticipantLeft, FileName, Refuse, TempMessage};
enum UserLogin{LoginT, RegisterT};

namespace Ui {
class UserLand;
}

class UserLand : public QDialog
{
    Q_OBJECT
    
public:
    explicit UserLand(QWidget *parent = 0);
    QTcpSocket *tcp;
    ~UserLand();
    
private slots:
    void on_loginBtn_clicked();

    void on_registerBtn_clicked();

    void displayError(QAbstractSocket::SocketError);
    void readMessage();

private:
    Ui::UserLand *ui;
    void sendMessage();
    MessageType mType;
    QString clientPort;
    QString serverIP;
};

#endif // USERLAND_H
