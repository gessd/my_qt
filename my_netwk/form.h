#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form(QWidget *parent = 0);
    QNetworkAccessManager *manager;
    QString httpgetdata(QString url, QString content, int ftype, int second);
    QByteArray httpgetarrdata(QString url, QString content, int ftype, int second);
    ~Form();
    
private slots:
    void replyFinished(QNetworkReply *);
    void qbug();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
