#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <process.h>
#include <winbase.h>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFile>
#include <QTextCodec>
#include <QCryptographicHash>
#include <QLocalSocket>

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

/*
void MainWindow::temp()
{
    SYSTEM_INFO SysInfo;
    GetSystemInfo(&SysInfo);

    qDebug()<< tr("处理器掩码: ") << SysInfo.dwActiveProcessorMask;
    qDebug()<< tr("处理器个数: ") << SysInfo.dwNumberOfProcessors;
    qDebug()<< tr("处理器分页大小: ") << SysInfo.dwPageSize;
    qDebug()<< tr("处理器类型: ") << SysInfo.dwProcessorType;
    qDebug()<< tr("最大寻址单元: ") << SysInfo.lpMaximumApplicationAddress;
    qDebug()<< tr("最小寻址单元: ") << SysInfo.lpMinimumApplicationAddress;
    qDebug()<< tr("处理器等级: ") << SysInfo.wProcessorLevel;
    qDebug()<< tr("处理器版本: ") << SysInfo.wProcessorRevision ;

}
*/


unsigned __stdcall MainWindow::PrintThread1( PVOID pvParm )
{
    // 当前线程号
    volatile static long lTreadNum = 0;
    int iCurThread = InterlockedIncrement( &lTreadNum );

    for( int i = 0; i < 20; ++ i)
    {
        // 进入临界区
        EnterCriticalSection(&g_cs);
        // 对需要保护的资源进行操作
        qDebug() << "线程" << iCurThread << "打印:" << i;
        // 没此进入临界区后必须调用离开临界区函数
        LeaveCriticalSection(&g_cs);
    }

    return 0;
}

// 使用TryEnterCriticalSection在获取资源不成功时会立刻返回，这时可以进行一些其它的操作后，再尝试进入
unsigned __stdcall MainWindow::PrintThread2( PVOID pvParm )
{
    volatile static long lTreadNum = 0;
    int iCurThread = InterlockedIncrement( &lTreadNum );

    // 记录尝试进入临界区的次数
    int iTryEnterTimes = 0;
    for( int i = 0; i < 20; ++ i)
    {
        // 进入临界区不成功时，尝试次数加1
        while( !TryEnterCriticalSection(&g_cs) )
        {
            ++iTryEnterTimes;
        }
        qDebug() << "线程" << iCurThread << "打印:" << i << "  TryTimes:" << iTryEnterTimes;
        iTryEnterTimes = 0;
        LeaveCriticalSection(&g_cs);
    }

    return 0;
}

// 启动线程并等待线程返回的函数
void MainWindow::StartThread( unsigned int (__stdcall * ThreadFuc)( void *) )
{
    HANDLE hThread1 = (HANDLE)_beginthreadex(NULL, 0, ThreadFuc, NULL, 0, NULL);
    HANDLE hThread2 = (HANDLE)_beginthreadex(NULL, 0, ThreadFuc, NULL, 0, NULL);

    if( hThread1 != NULL )
    {
        WaitForSingleObject(hThread1, INFINITE);
        CloseHandle(hThread1);
    }

    if( hThread2 != NULL )
    {
        WaitForSingleObject(hThread2, INFINITE);
        CloseHandle(hThread2);
    }
}

void MainWindow::temp()
{
    char moduleFileName[MAX_PATH];
    GetModuleFileNameA(0, moduleFileName, MAX_PATH);
    qDebug()<< moduleFileName;
    strcpy(moduleFileName, strrchr(moduleFileName,'\\')+1);
    qDebug()<< moduleFileName;
//    strcpy(strrchr(moduleFileName,'\\')+1,"");
//    qDebug()<< moduleFileName;

    char result[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, result);
    qDebug()<< result;
}

void MainWindow::on_pushButton_clicked()
{
//    temp();
    QString ul = "http://www.baidu.com";
    QString data;
    data = get(ul);
    qDebug()<<data;
}

QString MainWindow::get(QString url)
{
    QNetworkAccessManager nm;

    QNetworkReply * rp=nm.get(QNetworkRequest(QUrl(url)));
    QEventLoop loop;
    nm.connect(rp,SIGNAL(finished()),&loop,SLOT(quit()));
    return (rp->readAll());
}


bool MainWindow::ReadFilefromPath(QString path, QString &da)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    da=file.readAll();
    file.close();
    return true;
}

bool MainWindow::ReadByteFilefromPath(QString path, QByteArray &da)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    da=file.readAll();
    file.close();
    return true;
}


void MainWindow::on_pushButton_2_clicked()
{
    QString str="E:/code/ddk/251/123.txt";
    QString data;
    QByteArray barr;
//    ReadFilefromPath(str, data);
//    qDebug()<<data;
    ReadByteFilefromPath(str, barr);
    qDebug()<<barr;

}


bool MainWindow::WriteFileToPath(QString path, QString da)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QTextCodec * codec=QTextCodec::codecForName("utf-8");
    QByteArray arr=codec->fromUnicode(da);
    file.write(arr);
    file.close();
    return true;
}

bool MainWindow::WritebyteFileToPath(QString path, QByteArray da)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    file.write(da);
    file.close();
    return true;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString str="E:/code/ddk/251/123.txt";
    QString data = "abcdefggg";
    QByteArray barr = "qwertyuipppppp";
    WriteFileToPath(str, data);
    WritebyteFileToPath(str, barr);
}

void MainWindow::on_pushButton_4_clicked()
{
    SHELLEXECUTEINFO ShellInfo;         //对文件或文件夹操作参数

    memset(&ShellInfo, 0, sizeof(ShellInfo));
    ShellInfo.cbSize = sizeof(ShellInfo);
    ShellInfo.hwnd = NULL;
    ShellInfo.lpVerb = L"open";     //打开操作
    ShellInfo.lpFile = L".\.\git\123.txt"; //此处写执行文件的绝对路径
    ShellInfo.nShow = SW_SHOWNORMAL;
    ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;

    BOOL bResult = ShellExecuteEx(&ShellInfo);
}

QString MainWindow::getFileMd5(QString filePath)
{
    QFile theFile(filePath);
    theFile.open(QIODevice::ReadOnly);
    QByteArray ba = QCryptographicHash::hash(theFile.readAll(),QCryptographicHash::Md5);
    theFile.close();
    QTextCodec * codec=QTextCodec::codecForName("utf-8");
    ba=codec->fromUnicode(ba.toHex().constData());
    QString data=ba.data();
    return data.toUpper();
}


void MainWindow::on_pushButton_5_clicked()
{
    QString str="E:/code/ddk/251/123.txt";
    QString smd;
    smd = getFileMd5(str);
    qDebug() << smd;
    mstr();
}

void MainWindow::mstr()
{
    QByteArray qByteArray("") ; //定义一个空QByteArray对象，记住括号内要有“”，否则所无效对象。
    qByteArray.append("daniel"); //后面添加字符串
    qDebug()<<"qByteArray = "<<qByteArray.data()<<"\n"; //返回数据指针
    qDebug()<<"The size of qByteArray is "<<qByteArray.size()<<"\n"; //返回大小，不保护末尾的‘\n’
    qDebug()<<"The number of occurrences of 'a' is "<<qByteArray.count('a')<<"\n"; //查询重复次数
    qByteArray.fill('a'); //更改填充值
    qDebug()<<"qByteArray = "<<qByteArray.data()<<"\n";
}
