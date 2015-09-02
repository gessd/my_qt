#include "dialog.h"
#include "ui_dialog.h"

#include <QHostAddress>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSqlQueryModel>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    info_init();
    sqlpant = "E:/git/my_qt/my_Server/data.db";

    model->insertRow(0);
    model->setItem(0, 0, new QStandardItem("1000"));
    model->setItem(0, 1, new QStandardItem("whh"));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::info_init()
{
    QList<QHostAddress>address = QNetworkInterface::allAddresses();
    foreach(QHostAddress add, address)
    {
        if(add.protocol() == QAbstractSocket::IPv4Protocol)
        {
            ui->comboBox->addItem(add.toString());
        }
    }
    ui->lineEdit->setText("6666");
    ui->startBtn->setEnabled(true);
    ui->stopBtn->setEnabled(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格的单元为只读属性，即不能编辑


    model = new QStandardItemModel(this);
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, tr("UID"));
    model->setHeaderData(1, Qt::Horizontal, tr("用户名"));
    model->setHeaderData(2, Qt::Horizontal, tr("IP"));

    ui->tableView->setModel(model);

}

void Dialog::updateStatus()
{
    MessageType type = NewParticipant;
    QByteArray dataByte;
    QDataStream out(&dataByte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    mytcpsocket.append(clientConnection);
    //QString clientInfo="Client "+clientConnection->peerAddress().toString()+" connected successfully";
    QString clientInfo = tr("用户：") +"192.168.0.120" +tr("接入");

    ui->textBrowser->append(clientInfo);
    connect (clientConnection, SIGNAL(readyRead()), this, SLOT(serverReadMessage()));
//    QStringList strlist;
//    strlist << QString::number(clientConnection->socketDescriptor()) << clientConnection->peerAddress().toString() << QString::number(clientConnection->peerPort());
//    if(sqlOpen(sqlpant))
//    {
//        qDebug() << tr("sqlinsert");
//        query.prepare("insert into soc_user(soc_descriptor, soc_ip, soc_port) values(:desc, :ip, :port)");
//        query.addBindValue(clientConnection->socketDescriptor());
//        query.addBindValue(clientConnection->peerAddress().toString());
//        query.addBindValue(clientConnection->peerPort());
//        query.exec();
//        QSqlQueryModel *model = new QSqlQueryModel;
//        model->setQuery("select * from soc_user");
//        ui->tableView->setModel(model);
//    }
}

void Dialog::serverReadMessage()
{
    int mType;
    int uid;
    QString uname;
    for(int i=0; i<mytcpsocket.length(); i++)
    {
        if(mytcpsocket[i]->bytesAvailable()>0)
        {
            QDataStream inData(mytcpsocket[i]->readAll());
            inData.setVersion(QDataStream::Qt_4_6);
            inData >> mType;

            QByteArray bArr;
            QDataStream outData(&bArr, QIODevice::WriteOnly);
            UserLogin uType;

            switch(mType)
            {
            case LoginUser:
                inData >> uid;
                if(sqlOpen(sqlpant))
                {
                    query.exec(QString("select id from user_list where id='%1'").arg(uid));
                    query.next();
                    if(uid == query.value(0).toInt())
                    {
                        uType = LoginT;
                        outData.setVersion(QDataStream::Qt_4_6);
                        outData << uType << query.value(0).toInt();
                        qDebug() << query.value(0).toInt();
                        mytcpsocket[i]->write(bArr);
                    }
                }
                break;
            case RegisterUser:
                break;
            }
        }
    }
}

void Dialog::updateSendStatus()
{

}

void Dialog::on_startBtn_clicked()
{
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress(ui->comboBox->currentText()), ui->lineEdit->text().toInt()))
    {
        QMessageBox::warning(this, tr("err"), tcpServer->errorString());
        return ;
    }
    connect(tcpServer, SIGNAL(newConnection()),this, SLOT(updateStatus()));
    ui->lineEdit->setReadOnly(true);
    ui->startBtn->setEnabled(false);
    ui->stopBtn->setEnabled(true);
    ui->textBrowser->append(tr("服务开启"));
    //updateStatus();
}

void Dialog::on_stopBtn_clicked()
{
    tcpServer->close();
    model->removeRows(0,model->rowCount());
    ui->lineEdit->setReadOnly(false);
    ui->startBtn->setEnabled(true);
    ui->stopBtn->setEnabled(false);
    ui->textBrowser->append(tr("服务关闭"));
}

bool Dialog::sqlOpen(QString pathstr)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathstr);
    if(db.open())
    {
        query = QSqlQuery::QSqlQuery(db);
        return true;
    }
    return false;
}
