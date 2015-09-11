#include "form.h"
#include "ui_form.h"
#include <QTextCodec>
#include <QEventLoop>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));

}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
//    manager->get(QNetworkRequest(QUrl("http://www.qter.org")));

    QEventLoop * loop=new QEventLoop();
    QTimer* tmer;
    tmer = new QTimer();
    connect(tmer, SIGNAL(timeout()), loop, SLOT(quit()));
    tmer->start(10000);
    qDebug()<<"--X--";
    loop->exec();
    qDebug()<<"++Y++";
    tmer->stop();
    tmer->deleteLater();
}

void Form::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString all = codec->toUnicode(reply->readAll());
    ui->textBrowser->setText(all);
    reply->deleteLater();
}

void Form::qbug()
{
    qDebug()<< "--X--";
}



void Form::on_pushButton_2_clicked()
{
    QString md5str=httpgetdata("http://192.168.0.41/AgentList","",1,60000);
    qDebug()<<md5str;
}

QString Form::httpgetdata(QString url, QString content, int ftype, int second)
{
    return this->httpgetarrdata(url,content,ftype,second).data();
}

QByteArray Form::httpgetarrdata(QString url, QString content, int ftype, int second)
{
    QByteArray arr;
    QNetworkAccessManager  Manager;
    Manager.setNetworkAccessible(QNetworkAccessManager::Accessible);
    QNetworkRequest reg;
    QNetworkReply * reply;
    QTimer * ft;
    reg.setUrl(QUrl(url));
    if (ftype==1){
        reg.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        reg.setHeader(QNetworkRequest::ContentLengthHeader,content.length());
        reply=Manager.post(reg,content.toLatin1());
    }
    else
    {
        reply=Manager.get(reg);
    }
    QEventLoop * loop=new QEventLoop();
    connect(reply,SIGNAL(finished()),loop,SLOT(quit()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),loop,SLOT(quit()));
    if (second>0)
    {
        ft=new QTimer();
        connect(ft,SIGNAL(timeout()),loop,SLOT(quit()));
        ft->start(second);
    }
    loop->exec();
    if (second>0)
    {
        ft->stop();
        ft->deleteLater();
    }
    loop->deleteLater();
    if (reply->error()==QNetworkReply::NoError)
    {
        arr=reply->readAll();
    }
    qDebug()<< reply->error();
    reply->abort();
    reply->deleteLater();
    return arr;
}


