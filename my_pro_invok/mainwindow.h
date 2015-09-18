#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QString mname READ getName WRITE setName);
    Q_PROPERTY(int mid READ getId WRITE setId);
    
public:
    explicit MainWindow(QWidget *parent = 0);
    Q_INVOKABLE QString getName();
    Q_INVOKABLE void setName(QString na);
    Q_INVOKABLE int getId();
    Q_INVOKABLE void setId(int nt);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
