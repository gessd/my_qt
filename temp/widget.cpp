#include "widget.h"
#include "ui_widget.h"
#include "dialog.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTableView>
#include <QTreeWidgetItem>
#include <QTableWidget>
#include <QListView>
#include <QStandardItemModel>

Widget::Widget(QWidget *parent) :
    QWidget(parent ,Qt::WindowStaysOnTopHint),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Dialog *dlg = new Dialog;
    connect(dlg, SIGNAL(sendData(int, QString)), this, SLOT(receiveData(int, QString)));
//    ui->lineEdit->setText(uname);
//    ui->label->setText(uname);
//    qDebug() << uname << uid;

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model = new QStandardItemModel();
    model->setColumnCount(5);
    model->setHeaderData(0,Qt::Horizontal,tr("卡号"));
    model->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    ui->tableView->setModel(model);
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

void Widget::strlist()
{
//    QList<QString> list;
//    list << "www" << "abc"<< "123456";
//    for(int i=0; i<list.size(); i++)
//    {
//        qDebug() << list[i];
//    }

    QListView*              iListView;
    QStandardItemModel*     iStandardItemModel;
    iListView = new QListView(this);
    iStandardItemModel = new QStandardItemModel(this);

     QStringList strList;
     strList.append("string1");
     strList.append("string2");
     strList.append("string3");
     strList.append("string4");
     strList.append("string5");
     strList.append("string6");
     strList.append("string7");
     // 获得这个strList的个数
     int nCount = strList.size();
     for (int i=0; i<nCount; ++i)
     {
         // const T &    at ( int i ) const  这个是函数原型，所以需要强转一下
         QString string = static_cast<QString>(strList.at(i));
         QStandardItem* item = new QStandardItem(string);
         iStandardItemModel->appendRow(item);
     }

     QList<QString>  list;
     list << "item1";
     list << "item2";
     list << "item3";
     list << "item4";
     QString string1("a");
     list << string1;
     list.append("b");
     int mCount = list.size();
     for (int j=0; j<mCount; ++j)
     {
         QString string2 = static_cast<QString>(list.at(j));
         QStandardItem* item2 = new QStandardItem(string2);
         iStandardItemModel->appendRow(item2);
     }

     iListView->setModel(iStandardItemModel);
     iListView->setGeometry(QRect(0, 0, 360, 640));

     iListView->show();
}


void Widget::on_pushButton_2_clicked()
{
    //strlist();
    qDebug() << uname << uid;
    ui->label->setText(uname);
    ui->lineEdit->setText(uname);
}

void Widget::receiveData(int uid, QString uname)
{
    qDebug() << uid << uname;
    ui->lineEdit->setText(QString::number(uid));
}

void Widget::global()
{
/*
    ui->label->setText(QString::number(uid));
    ui->lineEdit->setText(uname);
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(5);
    model->setHeaderData(0,Qt::Horizontal,tr("卡号"));
    model->setHeaderData(1,Qt::Horizontal,tr("姓名"));

    QStringList strlist;
    QStandardItem *item;
    strlist << QString::number(uid) << uname;
    ui->tableView->setModel(model);
*/

    QString str = tr("whh");
    int nt = 1122;
//    QStandardItemModel  *model = new QStandardItemModel();
//    model->setColumnCount(5);
    model->setHeaderData(0,Qt::Horizontal,tr("卡号"));
    model->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    model->setItem(0, 0, new QStandardItem(str));
    model->setItem(0, 1, new QStandardItem(QString::number(nt)));
//    ui->tableView->setModel(model);
}

void Widget::on_pushButton_3_clicked()
{
//    QStandardItemModel  *model = new QStandardItemModel();
    model->setItem(1, 0, new QStandardItem(uname));
    model->setItem(1, 1, new QStandardItem(QString::number(uid)));
//    ui->tableView->setModel(model);

}

void Widget::on_pushButton_4_clicked()
{
//    ui->tableView->insertAction();
//    model->setItem(5, 0, new QStandardItem("abc"));
//    model->setItem(5, 1, new QStandardItem("ddd"));
    model->insertRow(0);
    model->setItem(0, 0, new QStandardItem("abc"));
    model->setItem(0, 1, new QStandardItem("ddd"));
//    model->removeRows(0,model->rowCount());  //删除所有行
}


/*/ //////////////////////////////////////
// //////////////////////////////////////
// //////////////////////////////////////
ProgressBarDelegate::ProgressBarDelegate(QObject *parent)
: QItemDelegate(parent)
{

}

void ProgressBarDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(index.column() == 2)
    {
int progress = index.model ()->data(index, Qt::DisplayRole).toInt ();
        QStyleOptionProgressBarV2 progressBarOption;
        progressBarOption.state = QStyle:: State_Enabled;
        progressBarOption.direction = QApplication:: layoutDirection ();
        progressBarOption.rect = option.rect;
        progressBarOption.fontMetrics = QApplication:: fontMetrics ();
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.textAlignment = Qt:: AlignCenter;
        progressBarOption.textVisible = true;
        progressBarOption.progress = progress;
        progressBarOption.text = QString("%1%").arg(progressBarOption.progress);
        QApplication:: style ()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    } else {
return QItemDelegate::paint (painter, option, index);
}
}

TableModel::TableModel(QObject *parent)
: QAbstractTableModel(parent), arr_row_list(NULL)
{

}

TableModel::~TableModel(void)
{
    arr_row_list = NULL;
}

void TableModel::setHorizontalHeaderList(QStringList horizontalHeaderList)
{
    horizontal_header_list = horizontalHeaderList;
}

void TableModel::setVerticalHeaderList(QStringList verticalHeaderList)
{
    vertical_header_list = verticalHeaderList;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if(vertical_header_list.size() > 0)
        return vertical_header_list.size();

if(NULL == arr_row_list)
return 0;
else
return arr_row_list->size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if(horizontal_header_list.size() > 0)
        return horizontal_header_list.size();

if(NULL == arr_row_list)
return 0;
else if(arr_row_list->size() < 1)
return 0;
else
return arr_row_list->at(0).size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(NULL == arr_row_list)
        return QVariant();

    if(arr_row_list->size() < 1)
        return QVariant();

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole)
    {
        if(index.row() >= arr_row_list->size())
            return QVariant();
        if(index.column() >= arr_row_list->at(0).size())
            return QVariant();
        return arr_row_list->at(index.row()).at(index.column());
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole)
    {
        if(orientation==Qt::Horizontal) // 水平表头
        {
            if(horizontal_header_list.size() > section)
                return horizontal_header_list[section];
            else
                return QVariant();
        }
        else
        {
            if(vertical_header_list.size() > section)
                return vertical_header_list[section]; // 垂直表头
            else
                return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flag = QAbstractItemModel::flags(index);

    // flag|=Qt::ItemIsEditable // 设置单元格可编辑,此处注释,单元格无法被编辑
    return flag;
}

void TableModel::setModalDatas(QList< QStringList > *rowlist)
{
    arr_row_list = rowlist;
}

void TableModel::refrushModel()
{
    beginResetModel();
    endResetModel();

emit updateCount(this->rowCount(QModelIndex()));
}

视图：
TableView::TableView(QWidget *parent)
: QTableView(parent)
{
this->setAlternatingRowColors(true);
this->setStyleSheet( "QTableView{background-color: rgb(250, 250, 115);"
"alternate-background-color: rgb(141, 163, 215);}" );
this->setSelectionBehavior(QAbstractItemView::SelectRows);
this->horizontalHeader()->setStretchLastSection(true);
this->horizontalHeader()->setHighlightSections(false);
this->verticalHeader()->setVisible(false);
this->setShowGrid(false);
this->setEditTriggers(QAbstractItemView::NoEditTriggers);
this->setSelectionMode(QAbstractItemView::ExtendedSelection);

    model = new TableModel();
    this->setModel(model);
    this->initHeader();
    model->setModalDatas(&grid_data_list);
    progressbar_delegate = new ProgressBarDelegate();
    this->setItemDelegate(progressbar_delegate);

connect(model, &TableModel::updateCount, this, &TableView::updateCount);

    this->initHeader();
}

TableView::~TableView(void)
{
    if(progressbar_delegate) {
        delete progressbar_delegate;
        progressbar_delegate = NULL;
    }

    if(model) {
        delete model;
        model = NULL;
    }
    grid_data_list.clear();
}

void TableView::addRow(QStringList rowList)
{
    grid_data_list.append(rowList);
    model->refrushModel();
}

void TableView::remove()
{
QModelIndexList model_index_list = this->selectedIndexes();
int model_count = model_index_list.count();
if(model_count <= 0)
return;

QList list_row;
for(int i=model_count-1; i>=0; i--)
{
QModelIndex model_index = model_index_list.at(i);
int row = model_index.row();
if(!list_row.contains(row))
list_row.append(row);
}

if(list_row.isEmpty())
return;

qSort(list_row);

for(int i=list_row.count()-1; i>=0; i--)
{
grid_data_list.removeAt(list_row.at(i));
}

model->refrushModel();
}

void TableView::clear()
{
grid_data_list.clear();
model->refrushModel();
}

int TableView::rowCount()
{
return model->rowCount(QModelIndex());
}

void TableView::initHeader()
{
    QStringList header;
    header << tr("name") << tr("size") << tr("progress") << tr("speed") << tr("left time") << tr("state");
    model->setHorizontalHeaderList(header);
}

void TableView::changeValue()
{
//这里以10行尾列进行更新
int row_count = this->rowCount();
if(row_count < 10)
return;

for(int i=0; i<10; i++)
{
QStringList file_list = grid_data_list.at(i);
int progress = rand()0;
QStringList row_list;
row_list <<  file_list.at(0) << file_list.at(1) << QString::number(progress) << file_list.at(3) << file_list.at(4) << file_list.at(5);
grid_data_list.replace(i, row_list);
}

model->refrushModel();
}

*/



