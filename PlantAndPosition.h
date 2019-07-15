#ifndef NEWPUSHBUTTON_H
#define NEWPUSHBUTTON_H

#include <QPushButton>
#include<qdebug.h>
#include<QPropertyAnimation>
#include<QTimer>
#include"bullet.h"
#include<QVBoxLayout>
#include<QMovie>
#include"zooomb.h"
//这个是放可供选择的植物位置以及到时选择植物时候用的
class PlantAndPosition : public QPushButton
{
    Q_OBJECT
private:
    int row ;
    int lin ;
    int SelectNumber;
    int MoveStatex;
    int MoveStatey;
    int PlantID;
    QPoint coordinate;
    //上面六个参数记录了所有的位置信息

    bool IsPlant = false;//该布尔量判断是否有植物


public:
    void ActivePlantSearchDistance( PlantAndPosition* plant ,zooomb * zb[],int num,int distance,int time);
    int  GetPlantId();
    bool JudgeDistance(QPoint ZoombPoint, int distance);
    //构造函数传进来两个参数，一个是一开始的按钮图片路径，一个是鼠标按下去后显示的按钮图片的路径
    PlantAndPosition( QString normalImage, QString pressImg="" );
    void Change(int id);
    //下面的是静态公有成员，被全体成员共享，点击任何一个
    //草丛，静态公有成员都会发生改变，这样点击的草丛的所有信息就会被捕获到
     static  int Currentrow ;
     static  int Currentlin ;
     static  int CurrentSelectNumber;
     static  int CurrentMoveStatex;
     static  int CurrentMoveStatey;

     //这个代表是否重新点击了同一个草丛，因为点击同一个草丛不会改变两次公有静态成员，所以要
     //一个单独的参数判断是否重复点击
     static int chang;

    //下面的代表是否在进行植物选择，如果是，屏蔽掉所有植物按钮，直到选择植物点击确定或者点击
     //取消键才会解禁
     static bool IsSelect ;

    //这个两个是公有接口，负责记录它传进来的参数的图片路径
    QString normalImgPath;
    QString pressdImgPath;

    //这个是公有函数，代表按钮图片的缩放大小，第一个是x坐标缩放大小，第二个是y坐标
    void SetImgScale(double i, double j);

    //这个同样是设置图片大小的函数，不过单位改为了像素，这个是一开始的函数，由于像素缩放会有图片
    void setImgSize(int i,int j );

    //这个代表记录的图片类，代表的是覆盖在按钮上面的图片
    QPixmap pix;
    QPixmap secondpix;



    //向下跳跃，这个是动画实现效果，按钮按下去会向下跳跃，然后在弹回来，两个函数相辅相成
    void zoom1();
    //向上
    void zoom2();

    //鼠标按下的事件，这个是为了捕捉他的按钮的鼠标动作，用来屏蔽按钮
    void mousePressEvent(QMouseEvent* e);
    //鼠标抬起时间，事件重写
    void mouseReleaseEvent(QMouseEvent* e);

    //公有成员函数来初始化每一个状态
    void SetState(int a, int b, int c, int d, int e);
    void SetCoordinate(int x, int y);
    QPoint GetCoordinate();
    int GetX();
    int GetY();

    //改变植物是否种植的状态
     void ChangPlantState( );
     //改变植物是否正在选择的状态
    static void ChangSelectState( );
    //公有接口返回植物是否种植
    bool PlantState();

    static int ActiveNumber1;//计算激活植物用
    Bullet* MyBullet;//子弹
signals:
    void selectPlant();
};

#endif // NEWPUSHBUTTON_H
