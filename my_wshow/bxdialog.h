#ifndef BXDIALOG_H
#define BXDIALOG_H

#include <QDialog>

namespace Ui {
class bxDialog;
}

class bxDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit bxDialog(QWidget *parent = 0);
    Ui::bxDialog* bdialog;
    bool eventFilter(QObject *o, QEvent *e);
    ~bxDialog();
    
private:
    Ui::bxDialog *ui;
};

#endif // BXDIALOG_H
