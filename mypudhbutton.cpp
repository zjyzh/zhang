#include "mypudhbutton.h"
#include<QPushButton>
#include<QDebug>
#include<QPropertyAnimation>
//下面是构造函数
mypudhbutton::mypudhbutton(QString normalImage, QString pressImg )
{
    //保存正常显示路径和显示后显示的路径
    this->normalImgPath= normalImage;
    this->pressdImgPath=pressImg;

    //这个布尔变量代表图片是否加载成功，
    bool ret=pix.load(this->normalImgPath);

    if(!ret)
    {
        QString str=QString("%1 图片加载失败").arg(this->normalImgPath);
        qDebug()<< str;
        return;
    }

    //设定图片大小
    this ->setFixedSize(pix.width(), pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px; }");
    //设置图片
    this->setIcon(pix);
    //设置图片大小
    this->setIconSize(QSize(pix.width(), pix.height()));
}


void mypudhbutton::zoom1()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this , "geometry");

    //设定时间间隔
    animation->setDuration(200);
    //设置动态对象起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置动画对象结束
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::InOutQuart);
    //调用执行动画
    animation->start();
}
    //向上

void mypudhbutton::zoom2()
{

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    //设定时间间隔
    animation->setDuration(200);
    //设置动态对象起始位置
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    //设置动画对象结束
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::InOutQuart);
    //调用执行动画
    animation->start();


    }

    //鼠标按下的事件
void mypudhbutton::mousePressEvent(QMouseEvent* e)
{
     if(this->pressdImgPath != "") //如果构造函数传入的第二个参数不为空，那么要进行切换操作
     {
         QPixmap pix;
         bool ret = pix.load(this->normalImgPath);
         if(!ret)
         {
             qDebug()<<"图片1加载失败，傻屌";
             return;
         }
         //设定图片大小
         this ->setFixedSize(pix.width(), pix.height());
         //设置不规则图片样式
         this->setStyleSheet("QPushButton{border:0px; }");
         //设置图片
         this->setIcon(pix);
         //设置图片大小
         this->setIconSize(QSize(pix.width(), pix.height()));
      }
        //其它的事情交给父类处理
      QPushButton::mousePressEvent(e);
}
    //鼠标抬起时间，事件重写
void mypudhbutton::mouseReleaseEvent(QMouseEvent* e)
{
    if(this->pressdImgPath != "") //如果构造函数传入的第二个参数不为空，那么要进行切换操作
    {
        QPixmap pix;
        bool ret= pix.load(this->pressdImgPath);
        if(!ret)
        {
            qDebug()<<"图片2加载失败，傻屌";
            return;
        }
        //设定图片大小
        this ->setFixedSize(pix.width(), pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px; }");
        //设置图片
        this->setIcon(pix);
        //设置图片大小
        this->setIconSize(QSize(pix.width(), pix.height()));
     }
        //其它的事情交个父类处理
     return  QPushButton::mouseReleaseEvent(e);
}

void mypudhbutton::setImgSize(int i, int j)
{
    this ->setFixedSize(i, j);
    this->setIconSize(QSize(i, j));
}

//设置图片大小
void mypudhbutton::SetImgScale(double i, double j)
{
    this->setFixedSize(pix.width() *i, pix.height() *j);
    this->setIconSize(QSize(pix.width() *i, pix.height() *j));
}




