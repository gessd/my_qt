#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QUrl"
#include <QWebElement>
#include <QWebFrame>
#include "QWebPage"
#include "QMessageBox"
#include "QDebug"
#include <QNetworkInterface>
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dlog=new Dialog();
    dlog->fwindow=this;
    ui->webView->load(QUrl("shead.htm"));
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(loadobject()));
    connect(ui->webView->page()->mainFrame(),SIGNAL(loadFinished(bool)),this,SLOT(loadOver()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadobject()
{
    //qDebug()<<"load.mtk";
    ui->webView->page()->currentFrame()->addToJavaScriptWindowObject("mtk",this);
    //temp();
}

bool MainWindow::mslogin(QString name, QString pss, QString surl, QString type)
{
    if(userbl(name,pss,surl,type))
    {
        ui->webView->load(QUrl("sinfo.htm"));
        qDebug()<<"load";
        return true;
    }
    return false;
}

void MainWindow::loadOver()
{
    qDebug()<<"loadover";
    temp();
    sinspect();
}

void MainWindow::mup()
{
    ui->webView->load(QUrl("shead.htm"));
}


void MainWindow::on_pushButton_clicked()
{
    ui->webView->load(QUrl("shead.htm"));
}

bool MainWindow::userbl(QString name, QString pss, QString surl, QString type)
{
    //qDebug()<<name<<pss<<surl<<type;
    mname = name.trimmed();
    mpss = pss.trimmed();
    murl = surl.trimmed();
    mtype = type.trimmed();
    //qDebug()<<mname<<mpss<<murl<<mtype;
    if(this->mname.length() == 0)
    {
        QMessageBox::warning(this, "err", tr("用户名为空"));
        return false;
    }
    if(mname == "112233")
    {
        if(mpss == "111")
        {
            if(murl == "123")
            {
                return true;
            }
            else
            {
                qDebug()<<"url not";
                QMessageBox::warning(this, "err", tr("连接错误"));
                return false;
            }
        }
        else
        {
            qDebug()<<"pss not";
            QMessageBox::warning(this, "err", tr("用户名或密码错误"));
            return false;
        }
    }
    else
    {
        qDebug()<<"name not";
        QMessageBox::warning(this, "err", tr("用户名或密码错误"));
        return false;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    SetIpaddresstocombox();
}

void MainWindow::temp()
{
    QString stip= "192.168.0.111";
    SetIpaddresstocombox();
    roominfo();
    //ui->webView->page()->mainFrame()->evaluateJavaScript("cominfo('2222','"+stip+"')");
}

void MainWindow::SetIpaddresstocombox()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    //获取所有网络接口的列表
    int n=1;
    foreach(QNetworkInterface finterface,list)
    {
        QList<QNetworkAddressEntry> entryList = finterface.addressEntries();
        if (entryList.count()>1)
        {
            QString ipstr=entryList.at(1).ip().toString();
            ui->webView->page()->mainFrame()->evaluateJavaScript("addipinfo('"+ipstr+"')");
            n=n+1;
        }
    }
}

void MainWindow::roominfo()
{
    QString mroom=tr("第一考场");
    ui->webView->page()->mainFrame()->evaluateJavaScript("addroominfo('"+mroom+"')");
}

void MainWindow::currentip(QString strip)
{
    mip = strip.trimmed();
    QMessageBox::about(this, tr("当前IP"), tr("你选择的IP地址是：")+mip);
}

void MainWindow::currentroom(QString strroom)
{
    mroom = strroom.trimmed();
    QMessageBox::about(this, tr("当前考场"), tr("你选择的考场是：")+mroom);
}

void MainWindow::innext(QString strroom, QString strip)
{
    qDebug()<<strroom;
    qDebug()<<strip;
    if(!(strroom.isEmpty() || strip.isEmpty()))
    {
        ui->webView->load(QUrl("smachine.html"));
    }
    else
    {
        QMessageBox::about(this, tr("空"), tr("考场或本机IP为空"));
    }

}

bool MainWindow::roomnext(bool aux, QString ipmain)
{
    this->mmachine = aux;
    QMessageBox::about(this, tr("下一步"), tr("检查信息"));
    if(mmachine)
    {
        QMessageBox::about(this, tr("机器"), tr("管理机"));
        ui->webView->load(QUrl("sinspect.html"));
    }
    else
    {
        QMessageBox::about(this, tr("机器"), tr("备用管理机"));
        if(!ipmain.isEmpty())
        {
            this->mainip = ipmain.trimmed();
            QMessageBox::about(this, tr("备用"), mainip);
        }
    }
    return true;
}

void MainWindow::isline(int isline)
{
    if(isline)
    {
        QMessageBox::about(this, tr("模式"), tr("离线"));
    }
    else
    {
        QMessageBox::about(this, tr("模式"), tr("在线"));
    }
}

void MainWindow::sinspect()
{
    ui->webView->page()->mainFrame()->evaluateJavaScript("sinspect('在线考试','管理机', '"+mip+"', '"+mroom+"')");
}


