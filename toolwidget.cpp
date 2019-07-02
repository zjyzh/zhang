#include "toolwidget.h"

toolwidget::toolwidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("设置界面");
    this->resize(600,500);
    t1=new QPushButton(this);
    t1->setText("返回主界面");
    //返回开始界面
    connect(t1,&QPushButton::released,this,&toolwidget::sendSlot);
}


void toolwidget::sendSlot()
{
     emit returnhello();
}
