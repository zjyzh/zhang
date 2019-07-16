#include "playsence.h"
#include<qdebug.h>
#include<qpainter.h>
#include<qmenubar.h>
#include<mypudhbutton.h>
#include<qtimer.h>
#include<chooselevelscene.h>
#include<QLabel>
#include"audioplayer.h"

int playSence::n=0;
playSence::playSence(int index)
{

    //    QList<PlantAndPosition *> Active;

    setMouseTracking(true);

    point=QPoint(0,0);

    volatile int ActiveNumber=0;

    qDebug()<<"打开了第" <<index <<"关";

    this->leaveIndex=index;

    if(index <2 &&index >0)

    {
        Number = Number1;
        BoNumber=BoNumber1;


    }
    else if ( 2 <=index && index <=5){

        Number = Number2;

        BoNumber=BoNumber2;

    }
    else if(index <=8 &&index >6)
    {

        Number = Number3;

        BoNumber=BoNumber3;

    }
    else if(index <=10 &&index >8)
    {

        Number = Number4;

        BoNumber=BoNumber3;

    }
    //固定大小
    this->setFixedSize(1280,720);
    //设置标题
    this->setWindowTitle("");
    //设置图片
    this->setWindowIcon(QIcon(":/little/danao3.png"));

    //创建菜单栏
    QMenuBar * bar= menuBar();
    this->setMenuBar(bar);

    //创建开始菜单
    QMenu* startmenu = bar->addMenu("开始");

    //创建菜单项
    QAction *quitaction= startmenu->addAction("退出");

    //点击退出
        connect(quitaction,&QAction::triggered,[=](){
            this->close();

        });
    //音乐
        m_audioPlayer = new AudioPlayer(this);
        m_audioPlayer->startBGM();

        //血量
    //    QLabel* showHP = new QLabel(this);
    //    QPixmap xue;
        //加载血条
        xue.load(QString(":/PVZ/blood%1.png").arg(7-HP));
        xue=xue.scaled(xue.width()*0.5,xue.height()*0.6);
        showHP->move(870,100);
        showHP->setPixmap(xue);
        showHP->setFixedSize(xue.width(),xue.height()*0.6);
        showHP->setAttribute(Qt::WA_TransparentForMouseEvents);
        showHP->show();
    //加载金币
        guang.load(QString(":/PVZ/kuang.png"));
        guang = guang.scaled(guang.width(),guang.height());
        showGold->move(100,75);
        showGold->setPixmap(guang);
        showGold->setFixedSize(guang.width(),guang.height());
        showGold->show();
        Gold->move(118,86);
        Gold->setNum(gold);

    //加载脑子图片和剩余血量
        HaoNaozi.load(QString(":/PVZ/danao%1.png").arg((7-HP)));
        HaoNaozi=HaoNaozi.scaled(HaoNaozi.width()*0.2,HaoNaozi.height()*0.2);
        MyNaoZi->setFixedSize(HaoNaozi.width(),HaoNaozi.height());
        MyNaoZi->setPixmap(HaoNaozi);
        MyNaoZi->move(this->width()-MyNaoZi->width()-200,(this->height()-MyNaoZi->height())/3);
        MyNaoZi->show();




        //添加返回按钮
        mypudhbutton *backbtn= new mypudhbutton(":/little/fanhui111.png");
        backbtn->SetImgScale(0.7,0.7);
        backbtn->setParent(this);
        //返回按钮的位置
        backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

        connect(backbtn,&mypudhbutton::clicked,[=](){
            backbtn->zoom1();
            backbtn->zoom2();
            qDebug()<<"你按下了玩游戏的地瓜";
            //按下返回按钮，延时发送信号
            QTimer::singleShot(100,this,[=](){
                emit back1();
                qDebug()<<"玩游戏地瓜信号发出去了";
            });
        });

    //设置僵尸类，Number代表僵尸类的数目
      zb= new zooomb*[Number];
    qDebug()<<"玩家场景里面的敌人数量"<<Number;
    for (int i=0;i<Number;i++)
    {
        if(i>15)
        {
            zb[i]= new zooomb(":/youxi/zoombgif.gif",30);
        }
        else
        {
             zb[i]= new zooomb(":/youxi/zoombgif.gif");
        }
           qDebug()<<i;
            zb[i]->setParent(this);
            zb[i]->move( -100,180 );
            zb[i]->setFixedSize(120,120);
            zb[i]->SetZoombID(i);
            zb[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
            zb[i]->show();

    }

    volatile int c=0;
    QTimer * timer = new QTimer(this);
    timer->start(1000);
    //每隔1000毫秒刷新一次，也就是每隔一秒钟出来一个僵尸
    connect(timer,&QTimer::timeout,[=]()mutable{
    //如果按下返回键，c变量清0，并且停止计时器
        connect(backbtn,&mypudhbutton::clicked,[=]() mutable {
            c=0;
            timer->stop();
        });
        if (c==Number)
        {
            timer->stop();
            c=0;
            //c代表增殖变量，如果c到僵尸数目了，那么c清0
        }
        else
        {
            qDebug()<<"第"<<c;
            //僵尸开始移动
            this->startMove( zb[c],15000,c);
            c++;
        }
    });

    //僵尸血条
    QLabel ** red =new QLabel*[Number];

    for(int i=0;i<Number;i++)
    {
        red[i]=new QLabel(this);

    }


    QTimer * timer1 = new QTimer(this);
    timer1->start(10);
//  QTimer * timer111 = new QTimer(this);
    //地图每隔10毫秒刷新僵尸血量判断僵尸死没死，每隔10毫秒
//    刷新僵尸位置，并且改变僵尸点的坐标
    connect(timer1,&QTimer::timeout,[=]()mutable {
        for (int i=0;i<Number;i++)
        {
            if(zb[i]!=NULL)
            {
                if(zb[i]->IsAlive()==false)
                {
                    qDebug()<<"僵尸死掉了"<<i;
                    zb[i]->RemoveXueTiao();
                    gold +=200;
                    Gold->setNum(gold);
                    delete zb[i];
                    DeadNumber = i;
                    zb[i]=NULL;
                }
            }
        }


        for (int i=0;i<Number;i++)
        {
        //这里改变僵尸位置和设置血条跟随
            if (zb[i]!=NULL&&red[i]!=NULL)
            {
                QPoint zbpos((zb[i]->x()+(zb[i]->rect().width())/2-40),
                             (zb[i]->y()+(zb[i]->rect().height())/2));

                if(zb[i]&&red[i])
                {
                    zb[i]->XueTiao=red[i];
                    const QString mSheetStyle1 = "min-width: 80px; min-height: 5px;max-width:80px; max-height: 5px;border-radius: 1px;  border:0px dashed red;background:red";
                    red[i]->setStyleSheet(mSheetStyle1);//改成 红色矩形
                    if(zb[i]->GetHP()>=0)
                    { red[i]->setFixedWidth(10*(zb[i]->GetHP()));}
                    red[i]->move(zb[i]->x(),zb[i]->y());
                    red[i]->show();
                    //红色血条跟随僵尸位置刷新
                    red[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
                }
                if(zb[i]->GetPoint()!=zbpos)
                {

                    zb[i]->GetPoint()=zbpos;
                    zb[i]->ChangePoint(zbpos.x(),zbpos.y());
                }
            }

        }

    });

    QTimer *timer5=new QTimer(this);
    timer5->start(1000);
//    每隔1秒判断游戏是否结束
    connect(timer5,&QTimer::timeout,[=]()mutable{

    if(HP<=0)
    {
        qDebug()<<"你输了，游戏结束";
       GameoverFail(zb);
       HP+=1000;
       timer->stop();
       timer1->stop();
       timer5->stop();
        IfLost=true;
    }


    for (int i=0;i<Number;i++)
    {
        if(NULL==zb[i])
        {
            n++;
//            qDebug()<<n;
        }
    }

    if(n==Number&&IfLost==false)
    {
        qDebug()<<"僵尸死光了";
        gameover();
        n-=Number;
        timer5->stop();
        timer1->stop();
        timer->stop();
        IfLost=false;
    }
    else
    {
        n=0;
    }

    //按下返回按钮之后清0

    });


    //僵尸动画结束代表它走到终点了，这个时候执行一系列操作
   //包括刷新HP，析构僵尸和扣血
    connect(this,&playSence::endAnimation,[=](int a){
        if(zb[a]!=NULL)
        {
            HP-=1;
            xue.load(QString(":/PVZ/blood%1.png").arg(7-HP));
            xue=xue.scaled(xue.width()*0.5,xue.height()*0.6);
            showHP->setPixmap(xue);
            showHP->show();
            showHP->setAttribute(Qt::WA_TransparentForMouseEvents);

            HaoNaozi.load(QString(":/PVZ/danao%1.png").arg((7-HP)/2));

            HaoNaozi=HaoNaozi.scaled(HaoNaozi.width()*0.2,HaoNaozi.height()*0.2);

            MyNaoZi->setPixmap(HaoNaozi);

            MyNaoZi->show();

            MyNaoZi->setAttribute(Qt::WA_TransparentForMouseEvents);

            //僵尸走到终点被析构了
            zb[a]->setParent(NULL);
            delete  zb[a];
            zb[a]= NULL;

        }
    });


    PlantAndPosition **  station = new PlantAndPosition*[StationNumber];
    //station代表塔基数量，
    //active代表的是已经激活的塔基数量
    PlantAndPosition **  Active = new PlantAndPosition*[StationNumber];
    qDebug()<<"玩家场景里面的塔基数量"<<StationNumber;
    for (int i=0;i<StationNumber;i++)
    {
        //            qDebug()<<"塔基初始化"<<i;

        Active[i]=NULL;
        station[i]= new PlantAndPosition(":/PVZ/button.png");

        station[i]->setImgSize(100,100);

        station[i]->setParent(this);


        station[i]->move( 65+ (i%9)*110, 60+(i/9)*140 );
        station[i]->SetState(i,i/9,i%9,85+ (i%9)*110,60+(i/9)*140);
        station[i]->SetCoordinate(85+ (i%9)*110+station[i]->width()/2,
                                  60+(i/9)*140+station[i]->height()/2);



    }
    //把路上的的
    delete station[0];
    station[0]=NULL;
    delete station[1];
    station[1]=NULL;
    delete station[9];
    station[9]=NULL;
    delete station[10];
    station[10]=NULL;
    delete station[16];
    station[16]=NULL;
    delete station[17];
    station[17]=NULL;
    delete station[19];
    station[19]=NULL;
    delete station[25];
    station[25]=NULL;
    for (int myi=28;myi<=34;myi++) {
        delete station[myi];
        station[myi]=NULL;
    }
    //常驻右边的选框
    QLabel* SelectKuang= new QLabel(this);
    QPixmap kuang ;
    kuang.load(":/PVZ/kuangkuang111.png");

    SelectKuang->setPixmap(kuang);
    SelectKuang->setFixedSize(kuang.width()*0.7,kuang.height()*0.6);
    SelectKuang->move(this->width()-SelectKuang->width(),(this->height()-SelectKuang->height())/3);

    //初始化四个选框植物，每个植物有不同id，分别为1,2,3,4
    Plant * SelectWanDou = new Plant(":/PVZ/wandou.png",":/PVZ/wandou111.png",1);
    Plant * SelectBingWanDou = new Plant(":/PVZ/bingwandou.png",":/PVZ/bingwandou111.png",2);
    Plant * SelectXiGua = new Plant(":/PVZ/xigua.png",":/PVZ/xigua111.png",3);
    Plant * SelectYuMi = new Plant(":/PVZ/yumi.png",":/PVZ/yumi111.png",4);


    SelectWanDou->setParent(this);
    SelectBingWanDou->setParent(this);
    SelectXiGua->setParent(this);
    SelectYuMi->setParent(this);

    //选框植物大小和格式

    SelectWanDou->SetImgScale(0.5,0.5,0.4,0.4);
    SelectBingWanDou->SetImgScale(0.5,0.5,0.4,0.4);
    SelectXiGua->SetImgScale(0.5,0.5,0.4,0.4);
    SelectYuMi->SetImgScale(0.5,0.5,0.4,0.4);

    SelectWanDou->setImgSize(100,100,100,100);
    SelectBingWanDou->setImgSize(100,100,100,100);
    SelectXiGua->setImgSize(100,100,100,100);
    SelectYuMi->setImgSize(100,100,100,100);

    SelectWanDou->move(this->width()-SelectBingWanDou->width()-20,
                       (this->height()-SelectBingWanDou->height()*4)/2-50);
    SelectBingWanDou->move(this->width()-SelectBingWanDou->width()-20,
                           (this->height()-SelectBingWanDou->height()*4)/2+SelectBingWanDou->height()-50);
    SelectXiGua->move(this->width()-SelectBingWanDou->width()-20,
                      (this->height()-SelectBingWanDou->height()*4)/2+SelectXiGua->height()*2-50);
    SelectYuMi->move(this->width()-SelectBingWanDou->width()-20,
                     (this->height()-SelectBingWanDou->height()*4)/2+SelectXiGua->height()*3-50);

    //确认按钮和取消按钮
    SelectButton * Confirm =new SelectButton(":/PVZ/confirm_11.png","",1);
    SelectButton * Cancel =new SelectButton(":/PVZ/quxiao1111111.png","",0);

    Confirm->setParent(this);
    Cancel->setParent(this);

    Confirm->move(this->width()-SelectBingWanDou->width()-160,
                  (this->height()-SelectBingWanDou->height()*4)/2+100);

    Cancel->move(this->width()-SelectBingWanDou->width()-160,
                 (this->height()-SelectBingWanDou->height()*4)/2+SelectXiGua->height()*3-100);

    //收到了选择按钮的发出来信号，
    //如果金币够了就买植物，否则无效
    connect(Confirm,&SelectButton::SentID,[=](int a)mutable{
        //qDebug()<<"现在是游戏场景里面的塔基，我收到了确认按钮发过来的信号"<<PlantAndPosition::CurrentSelectNumber;
        switch (a) {

        case 1:
            if(gold>=150)
            {
                gold-=150;
                Gold->setNum(gold);
                station[PlantAndPosition::CurrentSelectNumber]->Change(a);

                station[PlantAndPosition::CurrentSelectNumber]->MyBullet->setParent(this);

                station[PlantAndPosition::CurrentSelectNumber]->MyBullet->setAttribute(Qt::WA_TransparentForMouseEvents);

                qDebug()<<"激活前" <<PlantAndPosition::ActiveNumber1;
                ActiveNumber=PlantAndPosition::ActiveNumber1+1;

                Active[PlantAndPosition::ActiveNumber1+1]=station[PlantAndPosition::CurrentSelectNumber];

                qDebug()<<"激活了"<<ActiveNumber;

                station[PlantAndPosition::CurrentSelectNumber]->ChangPlantState();

                SelectButton::stateChange=false;

            }
            else {
                QLabel * TextMessage= new QLabel;
                TextMessage->setText("你的钱不够了，买不了植物");
                TextMessage->setFixedSize(this->width(),50);
                QPalette pe;//设置文本颜色，文本颜色是白色
                pe.setColor(QPalette::WindowText,Qt::red);
                TextMessage->setPalette(pe);
                QFont ft;
                ft.setPointSize(24);//设置文本大小

                TextMessage->setFont(ft);
                TextMessage->move(150,50);
                TextMessage->setParent(this);
                TextMessage->show();
                TextMessage->setAttribute(Qt::WA_TransparentForMouseEvents);
                QTimer::singleShot(2000,this,[=](){
                    TextMessage->hide();
                });
            }
            break;
        case 2: if(gold>=150)
            {
                gold-=150;
                Gold->setNum(gold);
                station[PlantAndPosition::CurrentSelectNumber]->Change(a);

                station[PlantAndPosition::CurrentSelectNumber]->MyBullet->setParent(this);

                station[PlantAndPosition::CurrentSelectNumber]->MyBullet->setAttribute(Qt::WA_TransparentForMouseEvents);

                qDebug()<<"激活前" <<PlantAndPosition::ActiveNumber1;
                ActiveNumber=PlantAndPosition::ActiveNumber1+1;

                Active[PlantAndPosition::ActiveNumber1+1]=station[PlantAndPosition::CurrentSelectNumber];

                qDebug()<<"激活了"<<ActiveNumber;

                station[PlantAndPosition::CurrentSelectNumber]->ChangPlantState();

                SelectButton::stateChange=false;
            }
            else {

                QLabel * TextMessage= new QLabel;
                TextMessage->setText("你的钱不够了，买不了植物");
                TextMessage->setFixedSize(this->width(),50);
                QPalette pe;//设置文本颜色，文本颜色是白色
                pe.setColor(QPalette::WindowText,Qt::red);
                TextMessage->setPalette(pe);
                QFont ft;
                ft.setPointSize(24);//设置文本大小

                TextMessage->setFont(ft);
                TextMessage->move(150,50);
                TextMessage->setParent(this);
                TextMessage->show();
                TextMessage->setAttribute(Qt::WA_TransparentForMouseEvents);
                QTimer::singleShot(2000,this,[=](){
                    TextMessage->hide();
                });
            }
            break;
        case 3:
            if(gold>=200)
            {
                gold-=200;
                Gold->setNum(gold);
                station[PlantAndPosition::CurrentSelectNumber]->Change(a);

                station[PlantAndPosition::CurrentSelectNumber]->MyBullet->setParent(this);

                station[PlantAndPosition::CurrentSelectNumber]->MyBullet->setAttribute(Qt::WA_TransparentForMouseEvents);

                qDebug()<<"激活前" <<PlantAndPosition::ActiveNumber1;
                ActiveNumber=PlantAndPosition::ActiveNumber1+1;

                Active[PlantAndPosition::ActiveNumber1+1]=station[PlantAndPosition::CurrentSelectNumber];

                qDebug()<<"激活了"<<ActiveNumber;

                station[PlantAndPosition::CurrentSelectNumber]->ChangPlantState();

                SelectButton::stateChange=false;
            }
            else {
                QLabel * TextMessage= new QLabel;
                TextMessage->setText("你的钱不够了，买不了植物");
                TextMessage->setFixedSize(this->width(),50);
                QPalette pe;//设置文本颜色，文本颜色是白色
                pe.setColor(QPalette::WindowText,Qt::red);
                TextMessage->setPalette(pe);
                QFont ft;
                ft.setPointSize(24);//设置文本大小

                TextMessage->setFont(ft);
                TextMessage->move(150,50);
                TextMessage->setParent(this);
                TextMessage->show();
                TextMessage->setAttribute(Qt::WA_TransparentForMouseEvents);
                QTimer::singleShot(2000,this,[=](){
                    TextMessage->hide();
                });
            }
            break;
        case 4:
            if(gold>=150)
            {
                gold-=150;
                Gold->setNum(gold);
                station[PlantAndPosition::CurrentSelectNumber]->Change(a);

                station[PlantAndPosition::CurrentSelectNumber]->MyBullet->setParent(this);

                station[PlantAndPosition::CurrentSelectNumber]->MyBullet->setAttribute(Qt::WA_TransparentForMouseEvents);

                qDebug()<<"激活前" <<PlantAndPosition::ActiveNumber1;
                ActiveNumber=PlantAndPosition::ActiveNumber1+1;

                Active[PlantAndPosition::ActiveNumber1+1]=station[PlantAndPosition::CurrentSelectNumber];

                qDebug()<<"激活了"<<ActiveNumber;

                station[PlantAndPosition::CurrentSelectNumber]->ChangPlantState();

                SelectButton::stateChange=false;
            }
            else {
                QLabel * TextMessage= new QLabel;
                TextMessage->setText("你的钱不够了，买不了植物");
                TextMessage->setFixedSize(this->width(),50);
                QPalette pe;//设置文本颜色，文本颜色是白色
                pe.setColor(QPalette::WindowText,Qt::red);
                TextMessage->setPalette(pe);
                QFont ft;
                ft.setPointSize(24);//设置文本大小
                TextMessage->setFont(ft);
                TextMessage->move(150,50);
                TextMessage->setParent(this);
                TextMessage->show();
                TextMessage->setAttribute(Qt::WA_TransparentForMouseEvents);
                QTimer::singleShot(2000,this,[=](){
                    TextMessage->hide();
                });
            }
            break;
        }

        SelectButton::stateChange=false;
        //无论钱够不够都解锁塔基选择状态，使塔基回到原来状态
        //如果植物改变了状态，也就是已经有植物在种着，那么会显示一个圆形框代表植物范围
        if(station[PlantAndPosition::CurrentSelectNumber]->PlantState())
        {

            point=QPoint(station[PlantAndPosition::CurrentSelectNumber]->GetCoordinate());
            QLabel *Circle=new QLabel;
            Circle->setParent(this);
            const QString mSheetStyle = "min-width: 400px; min-height: 400px;max-width:400px; max-height: 400px;border-radius: 200px;  border:1px dashed black;background:none";
            Circle->setStyleSheet(mSheetStyle);//改成 红色圆形
            Circle->move(point.x()-200,point.y()-200);
            Circle->show();
            Circle->setAttribute(Qt::WA_TransparentForMouseEvents);
        }


    });


    //一旦塔基被点击后会锁定，只要按取消按钮就可以解锁
    connect(Cancel,&SelectButton::SentID,[=](int a){
        //                    qDebug()<<"现在是游戏场景里面的塔基，我收到了取消按钮发过来的信号"<<PlantAndPosition::CurrentSelectNumber;
        SelectButton::stateChange=false;

    });

    //按下植物按钮会出现文本提示框，持续时间两秒
    connect(this,&playSence::changevalue,[=](){

        //  qDebug()<<"现在是在游戏场景"<<PlantAndPosition::CurrentSelectNumber;
        Cancel->UnlockCancleButton();
        QLabel * TextMessage= new QLabel;
        TextMessage->setText("请选择植物，选完后请按确认键确认，否则请按取消键");
        TextMessage->setFixedSize(this->width(),50);
        QPalette pe;//设置文本颜色，文本颜色是白色
        pe.setColor(QPalette::WindowText,Qt::white);
        TextMessage->setPalette(pe);
        QFont ft;
        ft.setPointSize(26);//设置文本大小
        //          TextMessage->setContentsMargins(22,15,10,25);//设置文本位置
        TextMessage->setFont(ft);
        TextMessage->move(150,50);
        TextMessage->setParent(this);
        TextMessage->show();
        TextMessage->setAttribute(Qt::WA_TransparentForMouseEvents);
        QTimer::singleShot(2000,this,[=](){
            TextMessage->hide();
        });


    });


    connect(this,&playSence::IdChange,[=](){
        //   qDebug()<<"我收到了植物id改变的信号并发到选择按钮那边去了";
        SelectButton::idchange(Plant::Id);
    });


    QTimer * timer44 = new QTimer(this);

    timer44->start(500);
//    这里是判断僵尸距离跟植物的距离是否离得够近，否则就开炮
    //射速是每隔500毫秒射一次
    connect(timer44,&QTimer::timeout,[=](){

        if(PlantAndPosition::ActiveNumber1>=0)
        {
            for (int i=0;i<=PlantAndPosition::ActiveNumber1;i++)
            {
                Active[i]->ActivePlantSearchDistance(Active[i],zb,Number,200,200);
            }
        }
    });


    //一旦按了返回按钮，将所有东西停止并析构
    connect(backbtn,&mypudhbutton::clicked,[=]()mutable{

        if(Confirm)
            delete Confirm;

        if(Cancel)
            delete Cancel;

        //            timer33->stop();
        timer44->stop();
        timer1->stop();
        timer5->stop();
        delete timer44;
        delete timer1;
        delete timer;


        delete   SelectWanDou;
        SelectWanDou=NULL;
        delete   SelectBingWanDou;
        SelectBingWanDou=NULL;
        delete   SelectXiGua;
        SelectXiGua=NULL;
        delete   SelectYuMi;
        SelectYuMi=NULL;


        PlantAndPosition::Currentrow=0 ;

        PlantAndPosition::Currentlin=0 ;

        PlantAndPosition::CurrentSelectNumber=0;

        PlantAndPosition::CurrentMoveStatex=0;

        PlantAndPosition::CurrentMoveStatey=0;

        //这个代表是否重新点击了同一个草丛，因为点击同一个草丛不会改变两次公有静态成员，所以要
        //一个单独的参数判断是否重复点击
        PlantAndPosition::chang=0;
        //下面的代表是否在进行植物选择，如果是，屏蔽掉所有植物按钮，直到选择植物点击确定或者点击
        //取消键才会解禁
        PlantAndPosition::IsSelect=false ;

        n=0;

        Plant::Id=0;

        Plant::chang=0;

        SelectButton::SelectID=0;
        SelectButton::stateChange=false;


        PlantAndPosition::ActiveNumber1=-1;
        for(int u=0;u<Number ; u++)
        {
            if(zb[u])
            {
                delete zb[u];
                zb[u]=NULL;
                //qDebug()<<"按了返回按钮的僵尸数组被删掉了" <<Number;
            }
        }
        for(int u=0;u<StationNumber ; u++)
        {

            if(station[u])
            {
                delete station[u];
                station[u]=NULL;
                //qDebug()<<"按了返回按钮的塔基数组被删掉了" <<StationNumber;
            }
        }
    });
}



//重写绘图事件，主要加载背景
void playSence::paintEvent(QPaintEvent *)
{


    QPainter painter(this);

    //设置背景
    QPixmap pix;
    pix.load(":/youxi/zmap444.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

//这个是僵尸动画，设置5个经过点，从头到尾串联
void playSence::startMove(zooomb * zb,int totalTime ,int ZoombNumber/*,bool w*/)
{

//    qDebug()<<"进入僵尸动画";

    if(zb!=NULL)
    {

//        qDebug()<<"僵尸动画不为0";
        QRect star(-100,180,-100,180);
        QRect end1(180,180,180,180);
        QRect end2(180,450,180,450);
        QRect end3(850,450,850,450);
        QRect end4(850,180,850,180);
        QRect end5(1000,180,1000,180);

        double Duration1=totalTime*0.15;
        double Duration2=totalTime*0.144;
        double Duration3=totalTime*0.358;
        double Duration4=totalTime*0.144;
        double Duration5=totalTime*0.1;

        QPropertyAnimation *  animation1 = new QPropertyAnimation(zb, "geometry");
        animation1->setDuration(Duration1);
        animation1->setStartValue(star);
        animation1->setEndValue(end1);

        QPropertyAnimation *  animation2 = new QPropertyAnimation(zb, "geometry");
        animation2->setDuration(Duration2);
        animation2->setStartValue(end1);
        animation2->setEndValue(end2);
        QPropertyAnimation *  animation3 = new QPropertyAnimation(zb, "geometry");
        animation3->setDuration(Duration3);
        animation3->setStartValue(end2);
        animation3->setEndValue(end3);
        QPropertyAnimation *  animation4 = new QPropertyAnimation(zb, "geometry");
        animation4->setDuration(Duration4);
        animation4->setStartValue(end3);
        animation4->setEndValue(end4);
        QPropertyAnimation *  animation5 = new QPropertyAnimation(zb, "geometry");
        animation5->setDuration(Duration5);
        animation5->setStartValue(end4);
        animation5->setEndValue(end5);

        animation1->start();
        connect(animation1, &QPropertyAnimation::finished, [=] {
            animation2->start();
//            qDebug()<<"结束动画信号发出去了2" ;
        });
        connect(animation2, &QPropertyAnimation::finished, [=] {
            animation3->start();
//            qDebug()<<"结束动画信号发出去了3" ;
        });
        connect(animation3, &QPropertyAnimation::finished, [=] {
            animation4->start();
//            qDebug()<<"结束动画信号发出去了4" ;
        });
        connect(animation4, &QPropertyAnimation::finished, [=] {
            animation5->start();
//            qDebug()<<"结束动画信号发出去了5" ;
        });


        connect(animation5, &QPropertyAnimation::finished, [=] {

                emit endAnimation(ZoombNumber);
                delete animation1;
                delete animation2;
                delete animation3;
                delete animation4;
                delete animation5;

        });

    }
    else {
        qDebug()<<"有空僵尸";
    }

}

//重写鼠标移动事件使得其能够实时监控是否有塔基状态改变，如果有就及时发送信号使得一系列反应
void  playSence::mouseMoveEvent(QMouseEvent *event)
{
   static int a=-10;

   if(a!=PlantAndPosition::chang)
   {

      a=PlantAndPosition::chang;
       emit changevalue();

   }

   static int b=-1;
   if(b!=Plant::chang)
   {
      b=Plant::chang;

       emit IdChange();

   }
}

//这个代表游戏赢了，弹出来模态对话框，锁定游戏
void playSence::gameover()
{
    QDialog dlg(this);
    dlg.resize(736 , 550);

    dlg.setStyleSheet("background-image:url(:/PVZ/win22.jpg);border:0px solid black;");

    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

    setAttribute(Qt::WA_TranslucentBackground);

    dlg.exec();//建立消息循环，防止对话框消失
    dlg.show();

    dlg.setAttribute(Qt::WA_DeleteOnClose);


}

//这个代表游戏输了，将剩下的僵尸都析构，使得游戏无法继续进行
void playSence::GameoverFail(zooomb** zb)
{

    for(int i=0;i<Number;i++)
    {
        if(zb[i]!=NULL)
          {
            zb[i]->RemoveXueTiao();
            delete zb[i];
            zb[i]=NULL;
        }
    }
    QDialog dlg(this);
        dlg.resize(867 , 649);

        dlg.setStyleSheet("background-image:url(:/PVZ/lost1.jpg);border:0px solid black;");

        setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

        setAttribute(Qt::WA_TranslucentBackground);

        dlg.exec();//建立消息循环，防止对话框消失
        dlg.show();

        dlg.setAttribute(Qt::WA_DeleteOnClose);

}
