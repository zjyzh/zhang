#include "play.h"

play::play(QWidget *parent) : QWidget(parent)
{


    this->setWindowTitle("设置界面");
    this->resize(1000,800);
    t1=new QPushButton(this);
    t1->setText("返回主界面");
    //返回开始界面
    connect(t1,&QPushButton::released,this,&play::sendSlot);
}


void play::sendSlot()
{
    emit returnhello();
}

