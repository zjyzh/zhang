#ifndef BULLET_H
#define BULLET_H

#include <QLabel>
#include<qpainter.h>
#include<qstring.h>
#include<QPixmap>
#include<QPaintEvent>
#include<QDebug>
#include<qmovie.h>
#include<QPropertyAnimation>
#include<QTimer>
#include<QPixmap>
#include<QPoint>
#include"zooomb.h"

const int PeaShooterDamage = 1;
const int IcePeaShooterDamage = 1;
const int WatermelonDamage = 2;
const int CornPeaShooterDamage = 2;
//定义伤害
class Bullet : public QLabel
{
    Q_OBJECT
    int Damage;
    QString FileName;
    QString HurtFileName;
    bool isrunning=false;
public:
//    explicit Bullet(QWidget *parent = nullptr);

    //构造函数里面要有植物ID，才能初始化子弹
    Bullet(int PlantID);
    //这个代表子弹从起点到终点的动画
    void Movemap(QRect startPoint, QRect endPoint, int time, zooomb* tarket);
    //这个代表子弹的大小
    void SetImgSize(int i, int j);
    //这个代表要攻击的目标
    void AttackTarket(zooomb *Tarket);
    //这个代表子弹打到敌人的效果
    void ChangeImg(QString Filename);

//    void COPY(Bullet * b);

    static bool IsAnimationRun;


signals:

public slots:
};

#endif // BULLET_H
