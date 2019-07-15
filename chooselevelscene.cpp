
#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<mypudhbutton.h>
#include<qdebug.h>
#include<QTimer>
#include<qlabel.h>
#include<QString>
chooselevelscene::chooselevelscene(QWidget *parent) : QMainWindow(parent)
{

    //固定大小
    this->setFixedSize(1280,720);
    //设置标题
    this->setWindowTitle("选择关卡");
    //设置标题旁边的图片
    this->setWindowIcon(QIcon(":/little/danao3.png"));

    //创建菜单栏
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);

    //创建开始菜单
    QMenu* startmenu = bar->addMenu("开始");

    //创建菜单项
    QAction *quitaction = startmenu->addAction("退出");

    //点击退出
    connect(quitaction, &QAction::triggered, [=](){
        this->close();

    });

    //添加返回按钮，这个按钮是自己定义的，构造函数是自己的图片
    mypudhbutton *backbtn = new mypudhbutton(":/little/fanhui111.png");
    backbtn->SetImgScale(0.7,0.7);
    //设置按钮的老爸
    backbtn->setParent(this);
    //改变按钮的位置
    backbtn->move(this->width()-backbtn->width(), this->height() - backbtn->height());
    //连接按钮，按钮按下去之后返回主菜单，这里调用了按钮的跳跃函数，代表按钮的动画
    connect(backbtn,&mypudhbutton::clicked, [=](){

        //两个按钮动画，跳下去跳上来
        backbtn->zoom1();
        backbtn->zoom2();
        //测试用的输出
        qDebug()<<"你按下了选择菜单的地瓜";
        //按下按钮，等他执行完动画效果延时发送信号
        //延时时间200毫秒
        QTimer::singleShot(200,this, [=](){
            emit back();
        });

    });

    playsence = NULL;


    //这里初始化了10个游戏场景，选择关卡
    for (int i=0;i<10;i++)
    {
        //这个一个字符串的拼接，%1代表的后面的i的内容，用来初始化不同关卡的不同图片
        QString str1 = QString(":/guanqia/%1.png").arg( i+1 );
        //这里初始化了按钮的图片:/guanqia/1.png代表第一关:/guanqia/2.png代表第二关，以此类推
        mypudhbutton *menuBtn = new mypudhbutton(str1);
        //新创建的按钮，设置老爸
        menuBtn->setParent(this);
        //按钮缩放
        menuBtn->SetImgScale(0.40,0.40);
        //连接具体的游戏场景
        connect(menuBtn,&QPushButton::clicked, [=](){

            //进入具体的游戏场景
            //游戏场景等到按下按钮之后才会初始化
            playsence = new playSence(i+1);

            playsence->show();
            this->hide();

            //游戏场景里面有一个返回按钮，代表的是退出，监听的是游戏场景里
            //发出的一个back1信号，收到信号返回选择菜单并删除析构

            connect(playsence,&playSence::back1, [=](){
                QTimer::singleShot(100,this, [=](){
                    qDebug()<<"收到信号了";
                    playsence->close();
                    delete playsence;
                    this->show();
                });

            });
        });

            //两个按钮左右之间的距离是150，上下的是200,旁边的150+是距离边框的距离
            menuBtn->move( 150 + (i%5) *200, 150 + (i/5) *250 );
            //用标签控件初始化数字，代表关卡里面的数字
            //关卡数字还没有调整，下面的代码看看就好
            QLabel* label = new QLabel(this);
            //标签控件跟按钮一样
            label->setFixedSize(150,150);
            //设置显示的内容
            label->setText(QString::number(i+1));
            //标签控件的位置
            label->move( 150 + (i%5) *200, 150 + (i/5) *250 );
            //label->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);  设置居中对齐

            QPalette pe;//设置文本颜色，文本颜色是白色
            pe.setColor(QPalette::WindowText, Qt::yellow);
            label->setPalette(pe);
            QFont ft;
            ft.setPointSize(38);//设置文本大小
            label->setContentsMargins(32,0,20,5);//设置文本位置
            label->setFont(ft);

            //设置鼠标穿透：
            label->setAttribute(Qt::WA_TransparentForMouseEvents);


}

}

//重写绘图事件
void chooselevelscene::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    //设置背景
    QPixmap pix;
    pix.load(":/little/bizhi0.jpg");
    //绘制背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置标题
    //pix.load(":/little/baoweinaoz.png");
    //可以进行缩放，现在没有进行缩放
   //pix = pix.scaled(pix.width(),pix.height());
    //这个是标题的位置，也就是那个“保卫脑子”的标志，不是文本
    //painter.drawPixmap(this->width()*0.27,-40,pix);


}






