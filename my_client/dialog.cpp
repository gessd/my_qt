#include "dialog.h"
#include "ui_dialog.h"

#include <QTcpSocket>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    tcp = NULL;
    serverIP = "192.168.0.127";
    clientPort = "6666";

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model = new QStandardItemModel();
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal, tr("UID"));
    model->setHeaderData(1,Qt::Horizontal, tr("NAME"));
    model->setHeaderData(2,Qt::Horizontal, tr("IP"));
    model->setHeaderData(3,Qt::Horizontal, tr("PORT"));
    ui->tableView->setModel(model);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::info_init()
{
    tcp = new QTcpSocket(this);
    tcp->connectToHost(serverIP, clientPort.toInt());
}
