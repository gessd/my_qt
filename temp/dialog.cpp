#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent, Qt::WindowStaysOnTopHint), //使窗口至于最上方
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    pathstr = ("E:/git/my_qt/temp/data.db");
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathstr);
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    nui = ui->lineEdit->text().toInt();
    int sqlu;
    if(db.open())
    {
        query = QSqlQuery::QSqlQuery(db);
        query.exec(QString("select id,username from user_list where id=%1").arg(nui));
        query.next();
        sqlu = query.value(0).toInt();
        ustr = query.value(1).toString();
        qDebug() << query.value(0);
        qDebug() << "select true";
//        QString name = db.connectionName();
//        QSqlDatabase::removeDatabase(name);
        db.close();
    }
    if(sqlu == nui)
    {
        QMessageBox::information(this, tr("ture"), tr("uname true"));
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("false"), tr("no id"));
        ui->lineEdit->clear();
        qDebug() << tr("无效");
    }
}

void Dialog::on_pushButton_2_clicked()
{
//    int i = ui->lineEdit->text().toInt();
    ustr = ui->lineEdit_2->text();
    if(db.open())
    {
        query = QSqlQuery::QSqlQuery(db);
        query.prepare("insert into user_list(username) values(:uname)");
//        query.addBindValue(i);
        query.addBindValue(ustr);
        query.exec();
        query.exec(QString("select * from user_list where username='%1'").arg(ustr));
        query.next();
        nui =query.value(0).toInt();
//        QMessageBox::warning(this, tr("true"), QString::number(nui));
        QMessageBox::information(this, tr("true"), QString::number(nui));
//        qDebug() << query.value(0);
//        QString name = db.connectionName();
//        QSqlDatabase::removeDatabase(name);
        db.close();

        accept();
//        emit sendData(nui, ustr);
//        qDebug() << "insert";
    }
}

void Dialog::on_pushButton_3_clicked()
{
    qDebug()<<"available drivers:";
    QStringList drivers = QSqlDatabase::drivers();
    foreach(QString driver, drivers)
        qDebug()<<driver;

    QSqlDatabase data_base = QSqlDatabase::addDatabase("QMYSQL");
    data_base.setHostName("10.0.31.41");  //设置主机地址
    data_base.setPort(3309);  //设置端口
    data_base.setDatabaseName("gv_local");  //设置数据库名称
    data_base.setUserName("root");  //设置用户名
    data_base.setPassword("root123");  //设置密码
    if(!data_base.open())
        qDebug()<<"failed to connect to mysql";
    else
        qDebug()<<"success";
    //close();
}

bool Dialog::sqlOpen()
{
    if(db.open())
    {
        query = QSqlQuery::QSqlQuery(db);
        return true;
    }
    return false;
}

void Dialog::myswitch()
{
    this->nswitch=1;
    switch(this->nswitch)
    {
    case 1:
        qDebug()<<1;
        this->nswitch = this->nswitch+1;
    case 2:
        qDebug()<<2;
        this->nswitch = this->nswitch+1;
        break;
    case 3:
        qDebug()<<3;
        this->nswitch = this->nswitch+1;
        break;
    case 4:
        qDebug()<<4;
        this->nswitch = this->nswitch;
    case 5:
        qDebug()<<5;
        this->nswitch = this->nswitch+1;
    case 6:
        qDebug()<<6;
        this->nswitch = this->nswitch+1;
    }
}

void Dialog::on_pushButton_4_clicked()
{
    myswitch();
}
