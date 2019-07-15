#include "selectbutton.h"
#include<QPushButton>
#include<QDebug>
#include<QPropertyAnimation>
//下面是构造函数
#include"playsence.h"
int SelectButton::SelectID =0;
bool SelectButton::stateChange=false;
SelectButton::SelectButton( QString normalImage, QString pressImg ,int selectID)
{
    //保存正常显示路径和显示后显示的路径
    this->normalImgPath= normalImage;
    this->pressdImgPath=pressImg;
    MYid=selectID;
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


void SelectButton::zoom1(){

QPropertyAnimation* animation= new QPropertyAnimation(this , "geometry");

//设定时间间隔
animation->setDuration(200);
//设置动态对象起始位置
animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
//设置动画对象结束

animation->setKeyValueAt(0.5, QRect(this->x(),this->y()+10,this->width(),this->height()));
//设置曲线
animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

animation->setEasingCurve(QEasingCurve::InOutQuart);

//调用执行动画
animation->start();

}


    //鼠标按下的事件
void SelectButton::mousePressEvent(QMouseEvent* e)
{

    if(SelectButton::stateChange==true)
    {
        qDebug()<<"这里选择按钮状态变为可选";
//        connect(this,&QPushButton::clicked,[=](){
        qDebug()<<"选择按钮被点了";

            if(this->MYid==1)
            {
                zoom1();
                emit SentID(Plant::Id);
                PlantAndPosition::IsSelect=false;
                qDebug()<<"选择按钮里面的确认按钮发出信号并将植物状态改为"<<PlantAndPosition::IsSelect;
                SelectButton::stateChange=false;
                emit SentID(Plant::Id);
            }
            else
            {
                zoom1();
                PlantAndPosition::IsSelect=false;
                qDebug()<<"选择按钮取消按钮，并改变状态状态改为"<<PlantAndPosition::IsSelect;
                SelectButton::stateChange=false;
                emit SentID(0);
            }

//        });
    }
    else if(cancal==100)
    {
        zoom1();
        PlantAndPosition::IsSelect=false;
        qDebug()<<"选择按钮取消按钮，并改变状态状态改为"<<PlantAndPosition::IsSelect;
        SelectButton::stateChange=false;
        emit SentID(0);
    }

{       qDebug()<<"这里的选择按钮事件给了父类";
        return QPushButton::mousePressEvent(e);
    }

        if(this->pressdImgPath !="") //如果构造函数传入的第二个参数不为空，那么要进行切换操作
        {
            QPixmap pix;
            bool ret= pix.load(this->normalImgPath);
            if(!ret)
            {
                qDebug()<<"图片1加载失败，傻屌";
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




        //其它的事情交个父类处理

}
    //鼠标抬起时间，事件重写
void SelectButton::mouseReleaseEvent(QMouseEvent* e)
{

        if(this->pressdImgPath !="") //如果构造函数传入的第二个参数不为空，那么要进行切换操作
        {
            QPixmap pix;
            bool ret= pix.load(this->pressdImgPath);
            if(!ret)
            {
                qDebug()<<"图片2加载失败，傻屌";
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
        //其它的事情交个父类处理
        QPushButton::mouseReleaseEvent(e);
}

void SelectButton::setImgSize(int i, int j)
{

    this ->setFixedSize(i,j);
this->setIconSize(QSize(i,j));

}
void SelectButton::SetImgScale(double i, double j)
{
    this ->setFixedSize(pix.width()*i,pix.height()*j);
    this->setIconSize(QSize(pix.width()*i,pix.height()*j));
}

//每点击一次塔基就会改变一次id，并发出信号
void SelectButton::idchange(int a)
    {
        SelectButton::SelectID=a;
        SelectButton::stateChange=true;
//        qDebug()<<"选择按钮收到了主场景发过来的id并改变了" <<SelectButton::SelectID <<SelectButton::stateChange;
    }

//一开始解锁取消按钮
void SelectButton::UnlockCancleButton()
{
    cancal=100;
}
