#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include "sqlite3.h"
using namespace std;

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

bool MainWindow::opendb()
{
    QString strdb =  "E:\\code\\ddk\\112255.db";
    if(QFile::exists(strdb) == false)
    {
        QMessageBox::warning(this, tr("err"), tr("db is no"));
        return false;
    }
    QByteArray barr = strdb.toLatin1();
    char* dbname = barr.data();
    int err;

    sqlite3_config(SQLITE_CONFIG_MULTITHREAD);
    sqlite3_initialize();
    err = sqlite3_open_v2(dbname, &this->sldb, SQLITE_OPEN_NOMUTEX|SQLITE_OPEN_READWRITE, NULL);
    if(err != SQLITE_OK)
    {
        QMessageBox::warning(this, tr("err"), tr("db is err"));
        return false;
    }

    return true;
}

void MainWindow::closedb(int type)
{
    if(sldb != NULL)
    {
        sqlite3_close(sldb);
        sldb = NULL;
        qDebug()<< "sldb is null";
    }
    if(type > 1)
    {
        if(pResult != NULL)
        {
            sqlite3_free_table(pResult);
            pResult = NULL;
        }
    }
}

bool MainWindow::quexec(QString sqlstr)
{
    string str = sqlstr.toStdString();
    char* err;
    if(opendb() == false)
    {
        QMessageBox::warning(this, tr("err"), tr("sql no open"));
        return false;
    }

    int nResult;
    nResult = sqlite3_exec(sldb, str.c_str(), NULL, NULL, &err);
    if(nResult != SQLITE_OK)
    {
        return false;
    }
    return true;
}

void MainWindow::on_pushButton_clicked()
{
//    QString str = "delete from Examination_Student where Examination_Student_code=11225518";
//    bool bl;
//    bl = quexec(str);
//    if(bl)
//    {
//        qDebug()<< "tuu";
//        closedb(1);
//    }

    bool bl;
    QString str = "select Examination_Student_code,Examination_Student_pass,Examination_Student_guid from Examination_Student where Examination_Student_code>11225556";
    bl = quexec_table(str);
    string strOut;

    for(int i=0; i<8; i++)
    {
        qDebug()<< pResult[i];
    }

//    int nIndex = nCol;
//    for(int i=0;i<nRow;i++)
//    {
//        for(int j=0;j<nCol;j++)
//        {
//            strOut+=pResult[j];
//            strOut+=":";
//            strOut+=pResult[nIndex];
//            strOut+="\n";
//            ++nIndex;
//        }
//    }
    sqlite3_free_table(pResult);
    qDebug()<< strOut.c_str();
    sqlite3_close(sldb);
    if(bl)
    {
        qDebug()<< "tuu";
        closedb(1);
    }

}

bool MainWindow::quexec_table(QString sqlstr)
{
    string str = sqlstr.toStdString();
    int nResult;

    if(opendb() == false)
    {
        QMessageBox::warning(this, tr("err"), tr("sql no open"));
        return false;
    }

    nResult = sqlite3_get_table(sldb,str.c_str(),&pResult,&nRow,&nCol,&errmsg);
    if (nResult != SQLITE_OK)
    {
        sqlite3_close(sldb);
        sqlite3_free(errmsg);
        return 0;
    }
    return true;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str = "abcdef";
    int nt = str.indexOf("f");
    qDebug()<< nt;
}

/*
#include <iostream>
using namespace std;
#include "sqlite/sqlite3.h"
int main()
{
    sqlite3* db;
    int nResult = sqlite3_open("test.db",&db);
    if (nResult != SQLITE_OK)
    {
        cout<<"打开数据库失败："<<sqlite3_errmsg(db)<<endl;
        return 0;
    }
    else
    {
        cout<<"数据库打开成功"<<endl;
    }

    char* errmsg;

    nResult = sqlite3_exec(db,"create table fuck(id integer primary key autoincrement,name varchar(100))",NULL,NULL,&errmsg);
     if (nResult != SQLITE_OK)
     {
         sqlite3_close(db);
         cout<<errmsg;
         sqlite3_free(errmsg);
        return 0;
    }
    string strSql;
    strSql+="begin;\n";
    for (int i=0;i<100;i++)
    {
        strSql+="insert into fuck values(null,'heh');\n";
    }
    strSql+="commit;";
    //cout<<strSql<<endl;

    nResult = sqlite3_exec(db,strSql.c_str(),NULL,NULL,&errmsg);

    if (nResult != SQLITE_OK)
    {
        sqlite3_close(db);
        cout<<errmsg<<endl;
        sqlite3_free(errmsg);
        return 0;
    }

    strSql = "select * from fuck";
    //nResult = sqlite3_exec(db,strSql.c_str(),callback,NULL,&errmsg);
    char** pResult;
    int nRow;
    int nCol;
    nResult = sqlite3_get_table(db,strSql.c_str(),&pResult,&nRow,&nCol,&errmsg);
      if (nResult != SQLITE_OK)
    {
        sqlite3_close(db);
        cout<<errmsg<<endl;
        sqlite3_free(errmsg);
        return 0;
    }

    string strOut;
    int nIndex = nCol;
    for(int i=0;i<nRow;i++)
    {
        for(int j=0;j<nCol;j++)
        {
            strOut+=pResult[j];
            strOut+=":";
            strOut+=pResult[nIndex];
            strOut+="\n";
            ++nIndex;
        }
    }
    sqlite3_free_table(pResult);
    cout<<strOut<<endl;
    sqlite3_close(db);
    return 0;
}
*/


