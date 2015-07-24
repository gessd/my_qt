#include "widget.h"
#include "ui_widget.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTableView>
#include <QTreeWidgetItem>
#include <QTableWidget>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:/git/my_qt/wl_tcpServer/data.db");
    if (db.open())
    {
        qDebug() << tr("open");
        QSqlQuery query;
        query.exec("select * from soc_user");
        while(query.next())
        {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            qDebug() << id << name;
        }
    }
//    QSqlQueryModel *myModel = new QSqlQueryModel;
//    myModel->setQuery("select * from student");
//    myModel->setHeaderData(0, Qt::Horizontal, tr("id"));
//    myModel->setHeaderData(1, Qt::Horizontal, tr("name"));
//    QTableView *view1 = new QTableView;
//    view1->setWindowTitle("mySqlQueryModel");       //修改窗口标题
//    view1->setModel(myModel);
//    view1->show();

    QSqlQueryModel *myModel = new QSqlQueryModel;
    myModel->setQuery("select * from soc_user");
    myModel->setHeaderData(0, Qt::Horizontal, tr("soc_descriptor"));
    myModel->setHeaderData(1, Qt::Horizontal, tr("soc_ip"));
    myModel->setHeaderData(2, Qt::Horizontal, tr("soc_port"));
    myModel->setHeaderData(3, Qt::Horizontal, tr("soc_type"));
    myModel->setHeaderData(4, Qt::Horizontal, tr("name"));
}

void Widget::temp()
{
    QTableWidget *tableWidget = new QTableWidget(10,5); // 构造了一个QTableWidget的对象，并且设置为10行，5列
   //    也可用下面的方法构造QTableWidget对象
   //    QTableWidget *tableWidget = new QTableWidget;
   //    tableWidget->setRowCount(10);     //设置行数为10
   //    tableWidget->setColumnCount(5);   //设置列数为5
   tableWidget->setWindowTitle("QTableWidget & Item");
   tableWidget->resize(350, 200);  //设置表格
//   QStringList header;
//   header<<"Month"<<"Description";
//   tableWidget->setHorizontalHeaderLabels(header);
   tableWidget->setItem(0,0,new QTableWidgetItem("Jan"));
   tableWidget->setItem(1,0,new QTableWidgetItem("Feb"));
   tableWidget->setItem(2,0,new QTableWidgetItem("Mar"));

   tableWidget->setItem(0,1,new QTableWidgetItem(QIcon("images/IED.png"), "Jan's month"));
   tableWidget->setItem(1,1,new QTableWidgetItem(QIcon("images/IED.png"), "Feb's month"));
   tableWidget->setItem(2,1,new QTableWidgetItem(QIcon("images/IED.png"), "Mar's month"));
   tableWidget->show();
}
