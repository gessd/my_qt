#ifndef TSKPAGE_H
#define TSKPAGE_H

#include <QObject>

class tskpage : public QObject
{
    Q_OBJECT
public:
    explicit tskpage(QObject *parent = 0);
    
signals:
    
public slots:
    void startexamm();
    void startoneexam(QString msg);
    QString starttowexam(QString msg);
};

#endif // TSKPAGE_H
