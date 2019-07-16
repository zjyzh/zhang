#include "SelectPlant.h"

int Plant::Id =0;
 int Plant::chang=0;
Plant::Plant( QString normalImage, QString pressImg ,int ID)
{
    //保存正常显示路径和显示后显示的路径

    this->ID=ID;

    this->normalImgPath= normalImage;
    this->pressdImgPath= pressImg;

    //这个布尔变量代表图片是否加载成功，
    bool ret=pix.load(this->normalImgPath);

    if(!ret)
    {
        QString str=QString("%1 图片加载失败").arg(this->normalImgPath);
        qDebug()<< str;
        return;
    }

    //设定图片大小
    this ->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式

    this->setStyleSheet("QPushButton{border:0px; }");

    //设置图片
    this->setIcon(pix);

    //设置图片大小

    this->setIconSize(QSize(pix.width(),pix.height()));


}


void Plant::zoom1(){

    QPropertyAnimation* animation= new QPropertyAnimation(this , "geometry");

    //设定时间间隔
    animation->setDuration(200);
    //设置动态对象起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置动画对象结束
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置曲线
    animation->setEasingCurve(QEasingCurve::InOutQuart);

    //调用执行动画
    animation->start();

}
//向上
void Plant::zoom2(){

    QPropertyAnimation* animation= new QPropertyAnimation(this , "geometry");

    //设定时间间隔
    animation->setDuration(200);
    //设置动态对象起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置动画对象结束
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置曲线
    animation->setEasingCurve(QEasingCurve::InOutQuart);

    //调用执行动画
    animation->start();

}

//鼠标按下的事件
void Plant::mousePressEvent(QMouseEvent* e)
{

    if( e->button()== Qt::LeftButton)
    {

        if(PlantAndPosition::IsSelect)
        {

            connect(this,&QPushButton::clicked,[=](){

                Plant::Id=this->ID;
                Plant::chang++;

            });

            if(pressdImgPath != "") //选中路径不为空，显示选中图片
            {
                QPixmap pixmap;
                bool ret = pixmap.load(pressdImgPath);
                if(!ret)
                {
                    qDebug() << pressdImgPath << "加载图片失败!";
                }

                this->setFixedSize( SecondImgX,SecondImgY );
                this->setStyleSheet("QPushButton{border:0px;}");
                this->setIcon(pixmap);
                this->setIconSize(QSize(pixmap.width()*SecondImgScaleX,pixmap.height()*SecondImgScaleY));
            }

        }
    }
    // 如果是鼠标右键按下
    else if(e->button() == Qt::RightButton)
    {

    }
    return QPushButton::mousePressEvent(e);

}
//鼠标抬起时间，事件重写
void Plant::mouseReleaseEvent(QMouseEvent* e)
{

    if( e->button()== Qt::LeftButton){
        if(PlantAndPosition::IsSelect)
        {
            {
                QPixmap pixmap;
                bool ret = pixmap.load(normalImgPath);
                if(!ret)
                {
                    qDebug() << normalImgPath << "加载图片失败!";

                }

                this->setFixedSize( FirstImgX,FirstImgY );
                this->setStyleSheet("QPushButton{border:0px;}");
                this->setIcon(pixmap);
                this->setIconSize(QSize(pix.width()*FirstImgScaleX,pix.height()*FirstImgScaleY));
                qDebug()<<"鼠标抬起了";
                Plant::Id=this->ID;
            }
        }
    }
    else if(e->button() == Qt::RightButton)
    {

    }


    return  QPushButton::mouseReleaseEvent(e);

}

void Plant::setImgSize(int i, int j,int x,int y)
{
    FirstImgX =i;
    FirstImgY =j;

    this ->setFixedSize(i,j);
    this->setIconSize(QSize(i,j));

    SecondImgX =x;
    SecondImgY =y;

}
void Plant::SetImgScale(double i, double j,double x,double y)
{
    FirstImgScaleX =i;
    FirstImgScaleY =j;

    this ->setFixedSize(pix.width()*i,pix.height()*j);
    this->setIconSize(QSize(pix.width()*i,pix.height()*j));

    SecondImgScaleX =x;
    SecondImgScaleY =y;

}

void Plant::plant(Plant* PL, int MoveX, int MoveY)
{

    PL->move(MoveX,MoveY);

}

//改变塔基的图片
void Plant::ChangeImg(int id)
{
    QPixmap pix;
    switch (id)
    {
    case Peashooter:
    {
        bool ret=pix.load(":/PVZ/pea.png");

        if(!ret)
        {
            QString str=QString("%1 图片加载失败").arg(":/PVZ/pea.png");
            qDebug()<< str;

        }

        //设定图片大小
        this ->setImgSize(100,100);

        //设置不规则图片样式

        this->setStyleSheet("QPushButton{border:0px; }");

        //设置图片
        this->setIcon(pix);
        this->SetImgScale(0.5,0.5,0.4,0.4);
        this->setImgSize(100,100,100,100);

    }
        break;
    case IcePeashooter:
    {
        bool ret=pix.load(":/PVZ/ice.png");

        if(!ret)
        {
            QString str=QString("%1 图片加载失败").arg(":/PVZ/ice.png");
            qDebug()<< str;

        }
        //设定图片大小
        this ->setImgSize(100,100);

        //设置不规则图片样式

        this->setStyleSheet("QPushButton{border:0px; }");

        //设置图片
        this->setIcon(pix);
        this->SetImgScale(0.5,0.5,0.4,0.4);
        this->setImgSize(100,100,100,100);
    }
        break;
    case Watermelon:
    {
        bool ret=pix.load(":/PVZ/water.png");

        if(!ret)
        {
            QString str=QString("%1 图片加载失败").arg(":/PVZ/water.png");
            qDebug()<< str;

        }

        //设定图片大小
        this ->setImgSize(100,100);

        //设置不规则图片样式

        this->setStyleSheet("QPushButton{border:0px; }");

        //设置图片
        this->setIcon(pix);
        this->SetImgScale(0.5,0.5,0.4,0.4);
        this->setImgSize(100,100,100,100);


    }
        break;
    case Corn:
    {
        bool ret=pix.load(":/PVZ/corn.png");

        if(!ret)
        {
            QString str=QString("%1 图片加载失败").arg(":/PVZ/corn.png");
            qDebug()<< str;

        }

        //设定图片大小
        this ->setImgSize(100,100);

        //设置不规则图片样式

        this->setStyleSheet("QPushButton{border:0px; }");

        //设置图片
        this->setIcon(pix);
        this->SetImgScale(0.5,0.5,0.4,0.4);
        this->setImgSize(100,100,100,100);

    }
        break;
    default:
        break;
    }



}







