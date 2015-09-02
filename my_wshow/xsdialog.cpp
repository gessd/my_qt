#include "xsdialog.h"
#include "ui_xsdialog.h"

#include "bxdialog.h"
#include "ui_bxdialog.h"
#include "mainwindow.h"
#include <QComboBox>
#include <QSpinBox>
#include "QDebug"

xsDialog::xsDialog(QWidget *parent) :
    bxDialog(parent),
    ui(new Ui::xsDialog)
{
    ui->setupUi(this);

    this->setMaximumHeight(400);
    this->setMaximumWidth(400);
    this->bdialog->verticalLayout->addWidget(ui->groupBox_main);
    ui->groupBox_login->setGeometry(0,0,300,200);
    this->showbox(ui->groupBox_login);
    ui->groupBox_main->setStyleSheet("QPushButton{background-color: rgb(205, 245, 245);border-radius:5px;}"
                                  "QPushButton:hover{background-color: rgb(230,230, 230);border-radius:5px;}"
                                  "QPushButton:pressed{background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0,203, 254, 255), stop:1 rgba(0, 181, 246, 255));border-radius:5px;}"
                                  "QLineEdit{border: 1px solid black;}");
}

xsDialog::~xsDialog()
{
    delete ui;
}

void xsDialog::showbox(QGroupBox *box)
{
    qDebug()<<"xx";
    ui->groupBox_info->hide();
    ui->groupBox_login->hide();
    box->setGeometry(0,0,300,200);
    box->show();
    this->freezeandrestoryui(box, true);
}

void xsDialog::initUi()
{
    MainWindow * fw=(MainWindow*)this->fwindow;
}

void xsDialog::freezeandrestoryui(QGroupBox *box,bool bl)
{
    for (int i=0;i<box->children().count();i++)
    {
        QString name=box->children().at(i)->metaObject()->className();
        if (name=="QLabel")
        {
            continue;
        }
        if (name=="QPushButton")
        {
            QPushButton * btn=(QPushButton*)box->children().at(i);
            btn->setEnabled(bl);
        }
        else if (name=="QComboBox")
        {
            QComboBox * cbox=(QComboBox*)box->children().at(i);
            cbox->setEnabled(bl);
        }
        if (name=="QLineEdit")
        {
            QLineEdit * edit=(QLineEdit*)box->children().at(i);
            edit->setEnabled(bl);
        }
        else if (name=="QSpinBox")
        {
            QSpinBox * sbox=(QSpinBox*)box->children().at(i);
            sbox->setEnabled(bl);
        }
    }
}

void xsDialog::on_pushButton_login_clicked()
{
    this->showbox(ui->groupBox_info);
}

void xsDialog::on_pushButton_clicked()
{
    MainWindow * fw=(MainWindow*)this->fwindow;
    this->hide();
}
