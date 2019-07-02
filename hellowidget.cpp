#include "hellowidget.h"

HelloWidget::HelloWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("保卫萝卜");
    b1.setParent(this);
    b2.setParent(this);
    b3.setParent(this);

    b1.move(100,350);
    b2.move(400,350);
    b3.move(250,350);

    b1.setText("进入游戏");
    b2.setText("退出游戏");
    b3.setText("设置");

    //对接
    connect(&b1,&QPushButton::released,this,&HelloWidget::changeplay);
    connect(&b2,&QPushButton::released,this,&HelloWidget::close);
    connect(&b3,&QPushButton::released,this,&HelloWidget::changetool);
    //与toolwidget,play对接
    connect(&w1,&toolwidget::returnhello,this,&HelloWidget::dealtool);
    connect(&w2,&play::returnhello,this,&HelloWidget::dealplay);
}
void HelloWidget::changetool()
{
    //设置窗口显示
    w1.show();
    //主窗口隐藏
    this->hide();
}
void HelloWidget::dealtool()
{
    w1.hide();
    show();
}
void HelloWidget::changeplay()
{
    //设置窗口显示
    w2.show();
    //主窗口隐藏
    this->hide();
}
void HelloWidget::dealplay()
{
    w2.hide();
    show();
}

HelloWidget::~HelloWidget()
{

}
