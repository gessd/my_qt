#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    QString mname;
    QString mpss;
    QString murl;
    QString mtype;
    QString mip;
    QString mroom;
    bool mmachine;
    QString mainip;
    void temp();
    ~MainWindow();


public slots:
    void loadobject();

    bool mslogin(QString name, QString pss, QString surl, QString type);
    void loadOver();
    void currentip(QString strip);
    void currentroom(QString strroom);
    void innext(QString strroom, QString strip);
    bool roomnext(bool aux, QString ipmain);
    void mup();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    bool userbl(QString name, QString pss, QString surl, QString type);
    void SetIpaddresstocombox();
    void roominfo();
    void sinspect();
};

#endif // MAINWINDOW_H
