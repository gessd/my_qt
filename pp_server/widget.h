#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QTcpServer;

namespace Ui {
class Widget;
}

enum userType
{
    newUser,
    leaveUser
};

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private:
    Ui::Widget *ui;
    QTcpServer *tcpServer;
    void waitMessage(userType type, QString Ip, QString User, QDataStream inMessage);
};

#endif // WIDGET_H
