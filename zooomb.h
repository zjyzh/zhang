#ifndef ZOOOMB_H
#define ZOOOMB_H
#include<qpainter.h>
#include<qstring.h>
#include<QPixmap>
#include<QPaintEvent>
#include<QLabel>
#include<QDebug>
#include<qmovie.h>
#include<QPropertyAnimation>
#include<QTimer>
#include<QObject>
#include<QThread>
#include<QPainter>
class playSence;
const int MaxZoombHP=30;
const int OriginalzoomHP=15;
class zooomb :public QLabel
{

    QPoint ZoombPoint;
    
    int a=0;

    int HP;

    int  ZoombId;
signals:

void PositionChange(int ID);
void endAnimation( int a );

public:
    //这个是一个僵尸类，它的父类是qlabel，它有了qlabel的特性
    //构造函数第一个参数是这个僵尸的图片，默认显示gif图，第二个代表它的hp
    //通过设置不同的Hp来设置不同的难度
    zooomb(QString filename, int Hp=10);

    //这个代表僵尸死了然后把血条给去掉
    void RemoveXueTiao(  );

    //每个僵尸都有自己的血条
    QLabel *XueTiao;

    //每个僵尸都有自己的ID
    void SetZoombID(int a);

    //僵尸掉血
    void GetAttack(int Damage );

    //得到僵尸的血量
    int GetHP();

    //判断僵尸死没死
    bool IsAlive();

    //这个传进去两个矩形参数，代表label的起点和终点，最后一个代表动画的持续时间，单位是毫秒
//   void Movemap(QRect startPoint, QRect endPoint, int time);
   void SetImgSize(int i, int j);
   //公有接口，记录连接的gif对象，方便修改图片大小
   QMovie *movie ;
    
   QPoint GetPoint();
   void ChangePoint(int x, int y);

};

#endif // ZOOOMB_H
