#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QStandardItemModel>
class QTcpSocket;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    QStandardItemModel  *model;
    QTcpSocket *tcp;
    ~Dialog();
    
private:
    Ui::Dialog *ui;
    void info_init();
    QString clientPort;
    QString serverIP;
};

#endif // DIALOG_H
