#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QNetworkInterface"

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


void MainWindow::getiplist()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    //获取所有网络接口的列表
    int x=1;
    foreach(QNetworkInterface finterface,list)
    {
        QList<QNetworkAddressEntry> entryList = finterface.addressEntries();
        if (entryList.count()>1)
        {
            QString ipstr=entryList.at(1).ip().toString();
            QString broadcast=entryList.at(1).ip().toString();
            QString netmask=entryList.at(1).broadcast().toString();
            if (ipstr!="" && broadcast!="" && netmask!="")
            {
                iplist.append(ipstr);
                x=x+1;
            }
        }
    }
    //qDebug()<<localIP;
//    QString ip="{\"returnFlag\":true,\"data\":{\"entries\":[";
//    for(int n=0; n<localIP.count()-1; n++)
//    {
//        ip+="{\"ip\":\"";
//        ip+=localIP.at(n);
//        ip+="\"},";
//    }
//    int ncount = localIP.count();
//    qDebug()<<ncount;
//    ip+="{\"ip\":\"";
//    ip+=localIP.at(ncount-1);
//    ip+="\"}]";
//    ip+="}}";
//    qDebug()<<ip;
}


QString MainWindow::strtojosn()
{
    QString strjson;
    QString flag="true";       //状态
    QString roomname;   //机房名字
    int ismain=0;         //是否管理机
    QString strip;      //本地IP

    strjson += "{\"returnFlag\":\"";
    strjson += flag;
    strjson += "\",\"data\":{";
    strjson += "\"machinename\":";
    if(0)                  //在线
    {
        strjson+="\"";
        strjson+=roomname;
        strjson+="\",";
    }
    else                    //离线
    {
        strjson+="[";
        for(int i=0; i<this->roomlist.count()-2; i+=2)
        {
            strjson+="{\"name\":\"";
            strjson+=this->roomlist.at(i);
            strjson+="\"},";
        }
        int ncountroom = this->roomlist.count();
        strjson+="{\"name\":\"";
        strjson+=this->roomlist.at(ncountroom-2);
        strjson+="\"}]";
    }

    strjson+=",\"ismainroom\":";
    strjson+=QString::number(ismain);

    if(!this->iplist.isEmpty())
    {
        strjson+=",\"entries\":[";
        for(int n=0; n<this->iplist.count()-1; n++)
        {
            strjson+="{\"ip\":\"";
            strjson+=this->iplist.at(n);
            strjson+="\"},";
        }
        int ncountip = this->iplist.count();
        strjson+="{\"ip\":\"";
        strjson+= this->iplist.at(ncountip-1);
        strjson+="\"}]";
    }
    else
    {
        strjson+=",\"entries\":\"\"";
    }
    strjson+="}}";
    return strjson;
}

void MainWindow::on_pushButton_clicked()
{
    //getiplist();
    QStringList slist;
    slist<<"五中考场二,ba5a8744-4f0e-45bc-ae71-8d76a379ad7f112255";//<<"五中考场一,666010c0-3f9d-47b7-9c1a-cdfa87995545112255";
    for (int i=0; i<slist.count(); i++)
    {
        this->roomlist=slist.at(i).split(",");
    }
    QString sjson;
    sjson = strtojosn();
    qDebug()<<sjson;
}
