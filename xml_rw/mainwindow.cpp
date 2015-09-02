#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtXml>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

/*
    QFile file("my.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement(tr("书库"));
    doc.appendChild(root);
    //
    QDomElement book = doc.createElement(tr("图书"));
    QDomAttr id = doc.createAttribute(tr("编号"));
    QDomElement title = doc.createElement(tr("书名"));
    QDomElement author = doc.createElement(tr("作者"));
    //
    QDomText text;
    id.setValue(tr("1"));
    book.setAttributeNode(id);
    text = doc.createTextNode(tr("QT"));
    title.appendChild(text);
    text = doc.createTextNode(tr("whh"));
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);
    //
    book = doc.createElement(tr("图书"));
    id = doc.createAttribute(tr("编号"));
    title = doc.createElement(tr("书名"));
    author = doc.createElement(tr("作者"));
    //
    id.setValue(tr("2"));
    book.setAttributeNode(id);
    text = doc.createTextNode(tr("红楼梦"));
    title.appendChild(text);
    text = doc.createTextNode(tr("曹雪芹"));
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::xmlselect()
{
    QFile file("my.xml");
    if(!file.open(QIODevice::ReadOnly))
        return;

    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorCol;
    if(!doc.setContent(&file, true, &errorStr, &errorLine, &errorCol))
    {
        qDebug() << errorStr << "line: " << errorLine << "col: " << errorCol;
        file.close();
        return ;
    }
    file.close();

    QDomElement domElem = doc.documentElement();
    QDomNode nDom = domElem.firstChild();
    while(!nDom.isElement())
    {
        QDomElement edom = nDom.toElement();
        QDomNodeList listdom = edom.childNodes();
        for(int i=0; i<listdom.count(); i++)
        {
            QDomNode nodedom = listdom.at(i);
            if(nodedom.isElement())
            {

            }
        }
        nDom = nDom.nextSibling();
    }
}

void MainWindow::on_btn_all_clicked()
{
    ui->listWidget->clear();
    QFile file("my.xml");
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QDomDocument doc;
    QString errstr;
    int errline;
    int errrow;
    if(!doc.setContent(&file, true, &errstr, &errline, &errrow))
    {
        qDebug() << errstr<< errline<< errrow;
        file.close();
        return;
    }
    file.close();

    QDomElement domelem = doc.documentElement();
    QDomNode n = domelem.firstChild();
    if(!n.isNull())
    {
        if(n.isEntity())
        {
            QDomElement e = n.toElement();
            ui->listWidget->addItem(e.tagName() +e.attribute(tr("编号")));
            QDomNodeList list = e.childNodes();
            for(int i=0; i<list.count(); i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                {
                   ui->listWidget->addItem(" " + node.toElement().tagName() + " :" + node.toElement().text());
                }
            }
        }
        n = n.nextSibling();
    }
}

void MainWindow::on_btn_select_clicked()
{
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("无法添加"));
    QFile file("my.xml");
    if(!file.open(QIODevice::ReadOnly()))
    {
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomElement book = doc.documentElement(tr("图书"));
    QDomAttr id = doc.createAttribute(tr("编号"));
    QDomElement title = doc.documentElement(tr("书名"));
    QDomElement author = doc.documentElement(tr("作者"));
    QDomText text;

    QString num = root.lastChild().toElement().attribute(tr("编号"));
    int count = num.toInt() +1;
    id.setValue(QString::number(count));
    book.setAttributeNode(id);
    text = doc.createTextNode(ui->lineEdit_name->text());
    title.appendChild(text);
    text = doc.createTextNode(ui->lineEdit_author->text());
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("添加成功"));
}
