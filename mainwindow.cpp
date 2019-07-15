#include "mainwindow.h"
#include<qpushbutton.h>
#include<qpainter.h>
#include<mypudhbutton.h>
#include<qdebug.h>
#include<qtimer.h>
#include<zooomb.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //创建菜单栏
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu* startmenu = bar->addMenu("开始");
    //创建菜单项
    QAction *quitaction = startmenu->addAction("退出");
    //点击退出
    connect(quitaction,&QAction::triggered, [=](){
        this->close();
    });

    //固定大小
    this->setFixedSize(1280,720);
    //设置标题
    this->setWindowTitle("保卫脑子");
    //设置图片
    this->setWindowIcon(QIcon(":/little/danao3.png"));

    //开始按钮创建
    mypudhbutton* startbtn = new mypudhbutton(":/little/kaishikaishi.png");
    //设置按钮
    mypudhbutton* setting_btn = new mypudhbutton(":/little/shezhisehzhi.png");
    //结束按钮
    mypudhbutton* end_btn = new mypudhbutton(":/little/tuichutuichu.png");
    //设置老爸
    startbtn->setParent(this);
    setting_btn->setParent(this);
    end_btn->setParent(this);
    //设置按钮的大小，这里用的是像素大小
    startbtn->setImgSize(395,193);
    setting_btn->setImgSize(287,71);
    end_btn->setImgSize(287,71);
    //设置按钮的位置，三个不同位置
    startbtn->move(this->width() *0.35,this->height() *0.6);
    setting_btn->move(this->width() *0.05,this->height() *0.86);
    end_btn->move(this->width() *0.75,this->height() *0.86);

    //必须先创建选择场景再连接开始按钮
    //创建第二个选择场景，再监听信号和开始
    //选择场景只要创建一次，不用跟关卡场景一样按了返回按钮就析构
    choose = new chooselevelscene;

    //这个监听的是选择场景里面的返回按钮的信号，代表返回主菜单，隐藏
    connect(choose,&chooselevelscene::back, [=](){
        choose->hide();
        this->show();
    });

    connect(startbtn,&QPushButton::clicked, [=](){
        //下面的是动画函数的调用
        startbtn->zoom1();
        startbtn->zoom2();
        //等动画执行完之后延时进入
        QTimer::singleShot(200,this, [=](){
            //将自己隐藏
            this->hide();
            choose->show();
        });
    });

    //创建第二个设置场景
    setting = new SettingMenu;

    //监听信号，设置场景里面也有返回主菜单的按钮
    connect(setting,&SettingMenu::back, [=](){
        setting->hide();
        this->show();
    });


    connect(setting_btn,&QPushButton::clicked, [=](){
        //下面的是动画函数的调用
        setting_btn->zoom1();
        setting_btn->zoom2();

        //等动画执行完之后延时进入
        QTimer::singleShot(200,this, [=](){
            //将自己隐藏
            this->hide();
            setting->show();
        });
    });

    connect(end_btn,&QPushButton::clicked, [=](){
        //下面的是动画函数的调用
        end_btn->zoom1();
        end_btn->zoom2();

        //等动画执行完之后延时进入
        QTimer::singleShot(200,this, [=](){
            //将自己隐藏
            this->close();
        });
    });
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//设置背景
    QPixmap pix;

    pix.load(":/little/bizhi111.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //设置标题
    pix.load(":/little/baoweinaoz.png");
    //可以进行缩放
    pix = pix.scaled(pix.width(),pix.height());

    painter.drawPixmap(this->width()*0.27,-40,pix);
}




MainWindow::~MainWindow()
{

}
