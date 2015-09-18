#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QUrl"
#include <QWebElement>
#include <QWebFrame>
#include "QWebPage"
#include "QMessageBox"
#include "QDebug"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pg=new tskpage(this);
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(loadobject()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->webView->load(QUrl("file:///E:/build/build-mhtp-mingw-Release/release/aa1.htm"));
}

void MainWindow::loadobject()
{
    qDebug()<<"sssssssssss";
    ui->webView->page()->currentFrame()->addToJavaScriptWindowObject("skplus",pg);            //↓↓↓↓↓
    //ui->webView->page()->currentFrame()->addToJavaScriptWindowObject("swfplus",this);         //会重载
}

void MainWindow::testkk()
{
    QMessageBox::about(0,"1","testkk");
}


void MainWindow::on_pushButton_2_clicked()
{
   // QVariant v=ui->webView->page()->mainFrame()->evaluateJavaScript("window.location.href");
    QVariant v=ui->webView->page()->mainFrame()->evaluateJavaScript("testurltwo()");
    qDebug()<<v.toString();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString ss="ffffffffffff";
    ui->webView->page()->mainFrame()->evaluateJavaScript("testurl('"+ss+"',2)");
}
