#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    emit msig();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool bl;
//    bl = connect(this, SIGNAL(msig()), this, SLOT(mslot()));
//    qDebug() << bl;

    bl = disconnect(this, SIGNAL(msig()), this, SLOT(mslot()));
    qDebug() << bl;

    bl = connect(this, SIGNAL(msig()), this, SLOT(mslot()));
    qDebug() << bl;
}

void MainWindow::mslot()
{
    QTime tm = QTime::currentTime();
    qDebug()<<tm;
}

void MainWindow::on_pushButton_2_clicked()
{
    emit msig();
    qDebug()<< "XX";
}
