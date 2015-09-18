#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getName()
{
    qDebug()<<"getName";
    return "getName";
}

void MainWindow::setName(QString na)
{
    qDebug()<<"setName";
    qDebug()<<na;
}

int MainWindow::getId()
{
    qDebug()<<"getId";
    return 2;
}

void MainWindow::setId(int nt)
{
   qDebug()<<"setId";
   qDebug()<<nt;
}

void MainWindow::on_pushButton_clicked()
{
    setProperty("mid", 2);
}

void MainWindow::on_pushButton_2_clicked()
{
    getName();
}
