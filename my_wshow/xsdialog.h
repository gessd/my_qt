#ifndef XSDIALOG_H
#define XSDIALOG_H

#include <QDialog>
#include "QMainWindow"
#include "bxdialog.h"
#include <QGroupBox>

namespace Ui {
class xsDialog;
}

class xsDialog : public bxDialog
{
    Q_OBJECT
    
public:
    explicit xsDialog(QWidget *parent = 0);
    QMainWindow * fwindow;
    void showbox(QGroupBox * box);
    void initUi();
    void freezeandrestoryui(QGroupBox *box,bool bl);
    ~xsDialog();
    
private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_clicked();

private:
    Ui::xsDialog *ui;
};

#endif // XSDIALOG_H
