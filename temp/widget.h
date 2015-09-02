#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    void temp();
    void strlist();
    void global();
    int uid;
    QStandardItemModel  *model;
    QString uname;
    ~Widget();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void receiveData(int uid, QString uname);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
