#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    QString ustr;
    int nui;
    ~Dialog();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Dialog *ui;
    QSqlQuery query;
    QString pathstr;
    QSqlDatabase db;
    bool sqlOpen();

signals:
    void sendData(int uid, QString uname);

};

#endif // DIALOG_H
