#include "settingmenu.h"
#include<qicon.h>
#include<qpainter.h>
#include<mypudhbutton.h>
#include<qdebug.h>
#include<qtimer.h>
SettingMenu::SettingMenu(QWidget *parent) : QWidget(parent)
{
    //固定大小
        this->setFixedSize(1280,720);
        //设置标题
        this->setWindowTitle("保卫脑子");
        //设置图片
        this->setWindowIcon(QIcon(":/little/danao3.png"));

    //添加返回按钮
            mypudhbutton *backbtn= new mypudhbutton(":/little/fanhui111.png");
            backbtn->SetImgScale(0.7,0.7);
            backbtn->setParent(this);

            backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

            connect(backbtn,&mypudhbutton::clicked,[=](){

            //动画执行
            backbtn->zoom1();
            backbtn->zoom2();
                qDebug()<<"你按下了地瓜";
                //按下按钮，延时发送信号
                QTimer::singleShot(200,this,[=](){
                     emit back();
                });

            });


}


void SettingMenu::paintEvent(QPaintEvent *)
    {

    QPainter painter(this);

        //设置背景
        QPixmap pix;
        pix.load(":/little/bizhi111.png");

        painter.drawPixmap(0,0,this->width(),this->height(),pix);

//        //设置标题
//        pix.load(":/little/baoweinaoz.png");
//        //可以进行缩放
//       pix = pix.scaled(pix.width(),pix.height());

//        painter.drawPixmap(this->width()*0.27,-40,pix);

    }



