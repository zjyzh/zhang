#ifndef PLANT_H
#define PLANT_H

#include <QPushButton>
#include<qdebug.h>
#include<QPropertyAnimation>
#include"PlantAndPosition.h"
#include<QMouseEvent>
const int SelectPeashooter =1;
const int SelectIcePeashooter = 2;
const int SelectWatermelon =3;
const int SelectCorn =4;
const int Peashooter =11;
const int IcePeashooter = 22;
const int Watermelon =33;
const int Corn =44;
//这个是选择植物类，也就是常驻右边的选框
//都有固定的ID，并且点击选择植物后图片会进行改变，从而增强点击效果
class Plant : public QPushButton
{
    Q_OBJECT
    int FirstImgX  =100 ;
    int FirstImgY  =100;
    int SecondImgX =80;
    int SecondImgY =80;

    double FirstImgScaleX  =1;
    double FirstImgScaleY  =1;
    double SecondImgScaleX =1;
    double SecondImgScaleY =1;

    int ID;

public:


        void plant(Plant* PL,int MoveX, int MoveY);

        void ChangeImg(int id);

        static int Id;

        static int chang;

        Plant( QString normalImage, QString pressImg="" ,int ID=0);
        //这个两个是共有接口，负责记录它传进来的参数的图片路径
        QString normalImgPath;
        QString pressdImgPath;
        //这个是公有函数，代表按钮图片的缩放大小，第一个是x坐标缩放大小，第二个是y坐标
        void SetImgScale(double i, double j,double x=1,double y=1);
        //这个同样是设置图片大小的函数，不过单位改为了像素，这个是一开始的函数，由于像素缩放会有图片
        //比例失真问题，因而一般不用他
        void setImgSize(int i,int j,int x =100 ,int y = 100);

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




signals:

        void selected(int a);

public slots:
};

#endif // PLANT_H
