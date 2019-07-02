#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include<QPushButton>
class toolwidget : public QWidget
{
    Q_OBJECT
public:
    explicit toolwidget(QWidget *parent = nullptr);
    void sendSlot();
signals:
    void returnhello();
public slots:
private:
    QPushButton *t1;
};

#endif // TOOLWIDGET_H
