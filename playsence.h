#ifndef PLAYSENCE_H
#define PLAYSENCE_H

#include<QMainWindow>
#include<zooomb.h>
#include<qthread.h>
#include<QPropertyAnimation>
#include<QList>
#include"PlantAndPosition.h"
#include"SelectPlant.h"
#include"mypudhbutton.h"
#include"selectbutton.h"
#include<QPoint>
#include"bullet.h"
#include"qmessagebox.h"
//这个是主要的游戏场景，构造函数代表的是他的关卡数，
class AudioPlayer;
//僵尸的数量，不同关卡可以有不同的数量
const int Number1 =  15;
const int Number2 =  24;
const int Number3 =  33;
const int Number4 =  45;
//塔基的数量
const int StationNumber = 45;

const  int BoNumber1 = 2;

const  int BoNumber2 = 3;

const  int BoNumber3 = 4;
class playSence : public QMainWindow
{
    Q_OBJECT
 QPoint point;

private:
   int HP=6;
   int Number;
   int BoNumber;//波数，现在还为设置
   int gold=500;//起始金币
   bool IfLost =false;
   int DeadNumber =0;


AudioPlayer *	m_audioPlayer;//--------音乐管理
signals:

 void back1();
 void start();
 void endAnimation( int a );
 void IdChange();
 void changevalue();
 void ChangeBoShu();


public:
static int n;
    void ChangeNaoZi(QLabel* Naozi, QPixmap Tupian );

    playSence(int index);



    zooomb **  zb;


    int leaveIndex;
    //画图事件，负责的是背景图以及一些素材载入
    void paintEvent(QPaintEvent *);
//    void paintEvent(QPaintEvent *,QPoint a);
    void startMove(zooomb * zb,int totalTime,int ZoombNumber/*,bool w*/);

//    QList<PlantAndPosition *> Active;
//通过鼠标移动事件监控全局，看是否有植物被点击或者被选择
void mouseMoveEvent(QMouseEvent *event);


    QLabel *showHP= new QLabel(this);

    QPixmap xue;

    QLabel *showGold = new QLabel(this);

    QPixmap guang;

    QPixmap HaoNaozi;

    QLabel *MyNaoZi= new QLabel(this);

    QLabel *Gold= new QLabel(this);



    void gameover();
    void GameoverFail(zooomb** zb);


};

#endif // PLAYSENCE_H
