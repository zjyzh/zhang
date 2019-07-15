#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H

#include <QWidget>
#include <QPushButton>
#include<QMouseEvent>
#include"SelectPlant.h"

//这个是一个自己定义的一个选择按钮类，继承qpushbutton，目前担任确认和取消职责
//可以实现大部分的按钮功能，同时又有自己的属性
class SelectButton : public QPushButton
{
    Q_OBJECT
    int MYid;
    int cancal =0;
public:

    static  int SelectID;
    static  bool stateChange;


    //构造函数传进来两个参数，一个是一开始的按钮图片路径，一个是鼠标按下去后显示的按钮图片的路径
    //如果没有第二个参数，那么默认调用的按钮按下去的动画
    //由于懒得准备第二张图片，那么本次游戏的所有图片都是默认按钮按下去的动画
    SelectButton( QString normalImage, QString pressImg="" ,int selectID=1);
    //这个两个是共有接口，负责记录它传进来的参数的图片路径
    QString normalImgPath;
    QString pressdImgPath;
    //这个是公有函数，代表按钮图片的缩放大小，第一个是x坐标缩放大小，第二个是y坐标
    void SetImgScale(double i, double j);
    //这个同样是设置图片大小的函数，不过单位改为了像素，这个是一开始的函数，由于像素缩放会有图片
    //比例失真问题，因而一般不用他
    void setImgSize(int i,int j );
    //这个代表记录的图片类，代表的是覆盖在按钮上面的图片
    QPixmap pix;
    //向下跳跃，这个是动画实现效果，按钮按下去会向下跳跃，然后在弹回来，两个函数相辅相成
    void zoom1();
    //向上
    void zoom2();

    //鼠标按下的事件，这个是为了捕捉他的按钮的鼠标动作，是用来显示两张不同图片的时候用的
    //当然以后也会有用
    void mousePressEvent(QMouseEvent* e);
    //鼠标抬起时间，事件重写
    void mouseReleaseEvent(QMouseEvent* e);
    static void idchange(int a);
    void UnlockCancleButton();

signals:

    void SentID(int id);

public slots:
};


#endif // SELECTBUTTON_H
