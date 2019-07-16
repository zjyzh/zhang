#include "zooomb.h"
#include"playsence.h"
zooomb::zooomb(QString filename, int Hp)
{
        HP=Hp;

        //这个是僵尸类的构造函数
        ZoombPoint=QPoint(this->x()+this->width()/2,this->y()+this->height()/2);
        QMovie * movie =new QMovie(filename);

        if(movie==NULL)
        {
            qDebug("僵尸图片加载不进来");
        }

         movie->setScaledSize(QSize(100,100));

        this->setStyleSheet("QLabel{border:0px ; }");
        this->setMovie(movie);
        //默认自动播放
        movie ->start();
//        this->setFixedSize(,100);

}

void zooomb::RemoveXueTiao(  )
{

    if (this->XueTiao)
    {
        delete  XueTiao;
    }
}


void zooomb::GetAttack(int Damage)
{
    this->HP-=Damage;
}




void zooomb::SetZoombID(int a)
{
    ZoombId =a;
}

int zooomb::GetHP()
{
    return HP;
}

bool zooomb::IsAlive()
{
    if(HP<=0)
        return false;
    else
        return true;
}

QPoint zooomb::GetPoint()
{
    return ZoombPoint;
}

void zooomb::ChangePoint(int x, int y)
{
    ZoombPoint=QPoint(x,y);

}


