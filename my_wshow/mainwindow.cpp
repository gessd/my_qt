#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMetaProperty>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pro_test();
    //mdialog = new xsDialog();
    //mdialog->fwindow=this;
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::GETfileName()
{
    return st_filename;
}

void MainWindow::SETfileName(QString str)
{
    st_filename = str;
}

void MainWindow::pro_test()
{
    QByteArray barr = "abc";
    this->setProperty(barr.data(), "");
    QString str = this->GETfileName();
    qDebug() << str;
}

bool MainWindow::maptoobj()
{
    /*
    1.QString转char *
    先将QString转换为QByteArray，再将QByteArray转换为char *。
    注意：不能用下面的转换形式char *mm = str.toLatin1().data();。
    因为这样的话，str.toLatin1()得到的QByteArray类型结果就不能保存，最后转换，mm的值就为空。
    */
        QMap<QString,QVariant>::Iterator fit;
        const  QMetaObject* metaObj = this->metaObject();
        int propertyCnt = metaObj->propertyCount();
        for ( int i = 1; i < propertyCnt; ++ i )
        {
            QMetaProperty oneProperty = metaObj->property( i );
            QString types=QVariant::typeToName(oneProperty.type());
            QString filedname=oneProperty.name();
            fit=this->fdataobj.find(filedname);
            QByteArray arr=filedname.toLatin1();
            if (fit==this->fdataobj.end())//如果原来的对象有值，不加下面的内容进行重新填充，就会有脏数据
            {
                if (types=="QString")
                {
                    this->setProperty(arr.data(),"");
                }
                else
                {
                    this->setProperty(arr.data(),0);
                }
                continue;
            }
            QVariant v=fit.value();
            if (v.type()==QVariant::DateTime)//数据库里的类型
            {
                this->setProperty(arr.data(),v.toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            }
            else
            {
                this->setProperty(arr.data(),v);//如果没有就出错，貌似不影响
            }
        }
        //下面的写法在不是用SELECT *的时候查询就会出现问题
        //    for (fit=this->fdataobj.begin();fit!=this->fdataobj.end();++fit)
        //    {
        //        QString name=fit.key();
        //        QByteArray arr=name.toLatin1();
        //        QVariant v=fit.value();
        //        this->setProperty(arr.data(),v);//如果没有就出错，貌似不影响
        //    }
        return true;
}


void MainWindow::on_pushButton_clicked()
{
    this->maptoobj();
}
