#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <stdio.h>
#include <QFileInfo>
#include <qDebug>

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

void MainWindow::temp()
{
    char buf[260];
    GetModuleFileNameA(NULL, buf ,MAX_PATH);
    qDebug()<< buf;
    strcpy(strrchr(buf,'\\')+1,"");
    qDebug()<< buf;
    QFileInfo finfo("F:\\aqt\\apro\\http\\arora-master.zip");
    qDebug() << finfo.isSymLink();
    qDebug() << finfo.absoluteFilePath();
    qDebug() << finfo.size();
    qDebug() << finfo.symLinkTarget();
    qDebug() << "**********************";
    QFileInfo info2(finfo.symLinkTarget());
    qDebug() << info2.isSymLink();
    qDebug() << info2.absoluteFilePath();
    qDebug() << info2.size();
}


void MainWindow::on_pushButton_clicked()
{
    temp();
}
