#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "xsdialog.h"
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ GETfileName WRITE SETfileName);
    
public:
    explicit MainWindow(QWidget *parent = 0);
    xsDialog* mdialog;

    QString st_filename;
    Q_INVOKABLE QString GETfileName();
    Q_INVOKABLE void SETfileName(QString str);
    void pro_test();

    bool maptoobj();
    QMap<QString,QVariant> fdataobj;

    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
