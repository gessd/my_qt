#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    CRITICAL_SECTION g_cs;
    unsigned __stdcall PrintThread1( PVOID pvParm );
    unsigned __stdcall PrintThread2( PVOID pvParm );
    void StartThread( unsigned int (__stdcall * ThreadFuc)( void *) );
    void temp();
    QString get(QString url);
    bool ReadFilefromPath(QString path, QString &da);
    bool ReadByteFilefromPath(QString path, QByteArray &da);
    bool WriteFileToPath(QString path, QString da);
    bool WritebyteFileToPath(QString path, QByteArray da);
    QString getFileMd5(QString filePath);
    void mstr();
    bool inidata();
    bool CrateArrNewmem(int NUM,qint64 size, QMap<QString, int> & fmap);
    void AddobjToMap(int num);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
