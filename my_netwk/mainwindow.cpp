#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkReply>
#include <QNetworkRequest>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nam = new QNetworkAccessManager(this);

    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedSlot(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QUrl url("http://www.hust.edu.cn/");
    QNetworkReply* reply = nam->get(QNetworkRequest(url));
    // NOTE: Store QNetworkReply pointer (maybe into caller).
    // When this HTTP request is finished you will receive this same
    // QNetworkReply as response parameter.
    // By the QNetworkReply pointer you can identify request and response.

}

void MainWindow::finishedSlot(QNetworkReply *reply)
{
#if 1
     // Reading attributes of the reply
     // e.g. the HTTP status code
     QVariant statusCodeV =reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
     // Or the target URL if it was a redirect:
     QVariant redirectionTargetUrl =reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
     // see CS001432 on how to handle this

     // no error received?
     if (reply->error() == QNetworkReply::NoError)
     {
         // read data from QNetworkReply here

         // Example 1: Creating QImage from the reply
         //QImageReader imageReader(reply);
         //QImage pic = imageReader.read();

         // Example 2: Reading bytes form the reply
         QByteArray bytes = reply->readAll();  // bytes
         //QString string(bytes); // string
         QString string = QString::fromUtf8(bytes);

         ui->textBrowser->setText(string);
     }
     // Some http error received
     else
     {
         // handle errors here
     }

     // We receive ownership of the reply object
     // and therefore need to handle deletion.
     reply->deleteLater();
#endif
}
