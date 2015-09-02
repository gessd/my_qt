#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sqlite3.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    bool opendb();
    void closedb(int type);
    bool quexec(QString sqlstr);
    int callback(void*,int,char**,char**);
    sqlite3 *sldb;

    bool quexec_table(QString sqlstr);
    char** pResult;
    char* errmsg;
    int nRow;
    int nCol;
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
