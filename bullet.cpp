#include "bullet.h"
#include"SelectPlant.h"

//传入的植物的ID，根据ID搭配子弹
Bullet::Bullet(int PlantID)
{

    switch (PlantID) {
    case Peashooter:
    {
        QPixmap  myPixmap ;
        myPixmap.load(":/PVZ/peabeat.png");

        if(myPixmap.load(":/PVZ/peabeat.png") == NULL)
        {
            qDebug("子弹图片加载不进来");
        }

        this->Damage = PeaShooterDamage;
        HurtFileName = ":/PVZ/peabeat.png";
        FileName = ":/PVZ/peabeat.png";
        myPixmap = myPixmap.scaled(myPixmap.width() *0.4 ,myPixmap.height() *0.4);
        this->setStyleSheet("QLabel{border:0px; }");
        this ->setFixedSize(myPixmap.width() ,myPixmap.height());
        this->setPixmap(myPixmap);
        break;

    }
    case IcePeashooter:
    {

        this->Damage = IcePeaShooterDamage;
        QPixmap  myPixmap;
        myPixmap.load(":/PVZ/icepeabeat.png");

        if(myPixmap.load(":/PVZ/icepeabeat.png") == NULL)
        {
            qDebug("子弹图片加载不进来");
        }
        HurtFileName = ":/PVZ/icepeabeat.png";
        FileName = ":/PVZ/icepeabeat.png";
        myPixmap = myPixmap.scaled(myPixmap.width() *0.4, myPixmap.height() *0.4);
        this->setStyleSheet("QLabel{border:0px; }");
        this ->setFixedSize(myPixmap.width() ,myPixmap.height());
        this->setPixmap(myPixmap);
        break;
    }

    case Watermelon:
    {
        this->Damage = WatermelonDamage;
        QPixmap  myPixmap ;
        myPixmap.load(":/PVZ/watermen.png");

        if(myPixmap.load(":/PVZ/watermen.png") == NULL)
        {
            qDebug("子弹图片加载不进来");
        }
        HurtFileName = ":/PVZ/watermen.png";
        FileName = ":/PVZ/watermen.png";
        myPixmap=myPixmap.scaled(myPixmap.width() *0.4, myPixmap.height() *0.4);
        this->setStyleSheet("QLabel{border:0px; }");
        this ->setFixedSize(myPixmap.width(), myPixmap.height());
        this->setPixmap(myPixmap);
        break;

    }
    case Corn:
    {

        this->Damage = CornPeaShooterDamage;

        QPixmap  myPixmap ;
        myPixmap.load(":/PVZ/butter.png");

        HurtFileName = ":/PVZ/Cornpult_butter_splat.png";
        if(myPixmap.load(":/PVZ/butter.png") == NULL)
        {
            qDebug("子弹图片加载不进来");
        }

        FileName = ":/PVZ/butter.png";
        myPixmap = myPixmap.scaled(myPixmap.width() *0.4, myPixmap.height() *0.4);
        this->setStyleSheet("QLabel{border:0px; }");
        this ->setFixedSize(myPixmap.width(), myPixmap.height());
        this->setPixmap(myPixmap);
        break;
    }

}
}

//攻击
void Bullet::AttackTarket(zooomb *Tarket)
{

    if(Tarket)
    Tarket->GetAttack(this->Damage);
}


//到了终点就改变图片
void Bullet::ChangeImg(QString Filename )
{
    QPixmap  myPixmap ;
    myPixmap.load(Filename);

    if(myPixmap.load(Filename) == NULL)
    {
        qDebug("子弹图片加载不进来");
    }
    myPixmap = myPixmap.scaled(myPixmap.width() *0.4, myPixmap.height() *0.4);
    this->setStyleSheet("QLabel{border:0px; }");
    this ->setFixedSize(myPixmap.width(), myPixmap.height());
    this->setPixmap(myPixmap);
}


//动画效果，第一个参数是开始的矩形，第二个是结束的，第三个是持续时间
void Bullet::Movemap(QRect startPoint, QRect endPoint, int time, zooomb* tarket)
{

    if(tarket)
    {
        int distance = ((startPoint.x() - endPoint.x()) * (startPoint.x() - endPoint.x())
                        + ((startPoint.y() - endPoint.y()) * (startPoint.y() - endPoint.y())));
        if(isrunning == false && distance <= 200*200)
        {

            isrunning = true;
            //        qDebug()<<"进入了动画效果";
            //        Bullet::IsAnimationRun=true
            this->ChangeImg(FileName);
            QPropertyAnimation *animation = new QPropertyAnimation(this , "geometry");
            //设定时间间隔
            animation->setDuration(time);
            //设置动态对象起始位置
            animation->setStartValue(startPoint);
            //设置动画对象结束
            animation->setEndValue(endPoint);
            //设置曲线，这里设定的是直线
            animation->setEasingCurve(QEasingCurve::Linear);
            //            animation->setLoopCount(10);
            //调用执行动画
            animation->start();
            this->show();
            connect(animation, &QPropertyAnimation::finished, [=](){
                //          qDebug()<<"子弹的动画结束了";
                //          Bullet::IsAnimationRun=false;
                isrunning = false;
                animation->stop();
                this->AttackTarket(tarket);
                this->ChangeImg(HurtFileName);
                this->hide();
            });
        }
    }
}
