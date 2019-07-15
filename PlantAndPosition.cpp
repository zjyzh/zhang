#include "PlantAndPosition.h"
#include"SelectPlant.h"

int  PlantAndPosition::CurrentSelectNumber = 6;
int  PlantAndPosition::Currentlin = 0;
int  PlantAndPosition::Currentrow = 0;
int  PlantAndPosition::CurrentMoveStatex = 0;
int  PlantAndPosition::CurrentMoveStatey = 0;
bool PlantAndPosition::IsSelect = false;
int PlantAndPosition::chang = 0;
int PlantAndPosition::ActiveNumber1 = -1;
//静态数据成员初始化
PlantAndPosition::PlantAndPosition(QString normalImage, QString pressImg )
{

    //保存正常显示路径和显示后显示的路径
    this->normalImgPath = normalImage;
    this->pressdImgPath = pressImg;

    //这个布尔变量代表图片是否加载成功，
    bool ret = pix.load(this->normalImgPath);

    if(!ret)
    {
        QString str = QString("%1 图片加载失败").arg(this->normalImgPath);
        qDebug()<<str;
        return;
    }

    //设定图片大小
    this->setImgSize(pix.width(), pix.height());

    //设置不规则图片样式

    this->setStyleSheet("QPushButton{border:0px; }");

    //设置图片
    this->setIcon(pix);

    //设置图片大小

    this->setIconSize(QSize(pix.width(), pix.height()));

}


void PlantAndPosition::zoom1(){

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");

    //设定时间间隔
    animation->setDuration(200);
    //设置动态对象起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置动画对象结束
    animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));

    //设置曲线
    animation->setEasingCurve(QEasingCurve::InOutQuart);

    //调用执行动画
    animation->start();

}
//向上
void PlantAndPosition::zoom2(){

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");

    //设定时间间隔
    animation->setDuration(200);
    //设置动态对象起始位置
    animation->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    //设置动画对象结束
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

    //设置曲线
    animation->setEasingCurve(QEasingCurve::InOutQuart);

    //调用执行动画
    animation->start();


}

//鼠标按下的事件

void PlantAndPosition::mousePressEvent(QMouseEvent* e)
{
    //如果正在选择或者有植物在上面，禁用这个按钮
    if(IsSelect||IsPlant)
    {
        return QPushButton::mousePressEvent(e);
    }
    else
    {
        if(IsPlant == false && IsSelect == false )
        {
            zoom1();
            zoom2();
            //按钮动画
            //改变静态成员表示按下的草丛的状态
            this->CurrentSelectNumber = SelectNumber;
            this->Currentlin = lin;
            this->Currentrow = row;
            this->CurrentMoveStatex = MoveStatex;
            this->CurrentMoveStatey = MoveStatey;
            this->chang++;
            PlantAndPosition::IsSelect = true;
            qDebug()<<"选择的值改变成了"<<this->CurrentSelectNumber;

            emit selectPlant();
        }

    }

    return QPushButton::mousePressEvent(e);
}
//鼠标抬起时间，事件重写
void PlantAndPosition::mouseReleaseEvent(QMouseEvent* e)
{

    if(this->pressdImgPath != "") //如果构造函数传入的第二个参数不为空，那么要进行切换操作
    {
        QPixmap pix;
        bool ret = pix.load(this->pressdImgPath);
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

    return QPushButton::mouseReleaseEvent(e);
}

void PlantAndPosition::setImgSize(int i, int j)
{

    this ->setFixedSize(i,j);
    this->setIconSize(QSize(i,j));

}
void PlantAndPosition::SetImgScale(double i, double j)
{
    this ->setFixedSize(pix.width() *i, pix.height() *j);
    this->setIconSize(QSize(pix.width() *i, pix.height() *j));
}

void PlantAndPosition::Change(int id)
{

    switch (id) {
    case SelectPeashooter:
    {

        //        for(int i=0;i<10;i++){
        //             MyBullet[i]= new Bullet(":/PVZ/peabeat.png");
        //           MyBullet[i]->setParent(this);
        //             MyBullet1[i]=NULL;
        //}
        //            QVBoxLayout* layout = new QVBoxLayout(this);

        //            QLabel* label = new QLabel();

        //            label->setAlignment(Qt::AlignHCenter);

        //            QMovie* movie = new QMovie(":/PVZ/PeaShooterSingle1.gif");

        //            movie->setScaledSize(QSize(100,100));

        //            label->setStyleSheet("QLabel{border:0px;background:none; }");

        //            label->setMovie(movie);

        //            layout->addWidget(label);

        //            movie->start();
        PlantID = Peashooter;
        MyBullet = new Bullet(PlantID);
        bool ret = pix.load(":/PVZ/pea1.png");
        if(!ret)
        {
            QString str = QString("%1 图片加载失败").arg(":/PVZ/pea1.png");
            qDebug()<< str;
        }


        bool ret1 = secondpix.load(":/PVZ/pea.png");

        if(!ret1)
        {
            QString str = QString("%1 图片加载失败").arg(":/PVZ/pea.png");
            qDebug()<< str;

        }



    }
        break;
    case SelectIcePeashooter:
    {
        PlantID = IcePeashooter;
        MyBullet = new Bullet(PlantID);
        bool ret = pix.load(":/PVZ/ice1.png");
        if(!ret)
        {
            QString str = QString("%1 图片加载失败").arg(":/PVZ/ice1.png");
            qDebug()<< str;

        }

        bool ret1 = secondpix.load(":/PVZ/ice.png");

        if(!ret1)
        {
            QString str=QString("%1 图片加载失败").arg(":/PVZ/ice.png");
            qDebug()<< str;

        }




        //            for(int i=0;i<10;i++){
        //                        MyBullet[i]= new Bullet(":/PVZ/icepeabeat.png");
        //                        MyBullet1[i]=NULL;
        ////                      MyBullet[i]->setParent(this);
        //            }



        //          QVBoxLayout* layout = new QVBoxLayout(this);

        //          QLabel* label = new QLabel();

        //          label->setAlignment(Qt::AlignHCenter);

        //          QMovie* movie = new QMovie(":/PVZ/snowpea1.gif");

        //          movie->setScaledSize(QSize(100,100));

        //          label->setStyleSheet("QLabel{border:0px;background:none; }");

        //          label->setMovie(movie);

        //          layout->addWidget(label);

        //          movie->start();

        //                  QMovie * movie =new QMovie(":/PVZ/pea1.gif");

        //                  if(movie==NULL)
        //                  {
        //                      qDebug("僵尸图片加载不进来");
        //                  }

        //                 movie->setScaledSize(QSize(100,100));
        //                  this->setStyleSheet("QLabel{border:0px; }");
        //                  this->setMovie(movie);
        //                  //默认自动播放
        //                  movie ->start();
        //            bool ret=pix.load(":/PVZ/ice1.png");

        //            if(!ret)
        //            {
        //                QString str=QString("%1 图片加载失败").arg(":/PVZ/ice1.png");
        //                qDebug()<< str;
        //            }
    }

        break;
    case SelectWatermelon:
    {
        PlantID=Watermelon;
        MyBullet=new Bullet(PlantID);
        bool ret=pix.load(":/PVZ/water1.png");

        if(!ret)
        {
            QString str=QString("%1 图片加载失败").arg(":/PVZ/water1.png");
            qDebug()<< str;

        }


        bool ret1=secondpix.load(":/PVZ/water1.png");

        if(!ret1)
        {
            QString str=QString("%1 图片加载失败").arg(":/PVZ/water1.png");
            qDebug()<< str;

        }





    } break;
        //            for(int i=0;i<10;i++){
        //                                  MyBullet[i]= new Bullet(":/PVZ/watermen.png");
        //                                  MyBullet1[i]=NULL;
        ////                                 MyBullet[i]->setParent(this);
        //                        }



        //           QVBoxLayout* layout = new QVBoxLayout(this);

        //           QLabel* label = new QLabel();

        //           label->setAlignment(Qt::AlignHCenter);

        //           QMovie* movie = new QMovie(":/PVZ/mellon1.gif");

        //           movie->setScaledSize(QSize(100,100));

        //           label->setStyleSheet("QLabel{border:0px;background:none; }");

        //           label->setMovie(movie);

        //           layout->addWidget(label);

        //           movie->start();
    case SelectCorn:
    {


        PlantID=Corn;
        MyBullet=new Bullet(PlantID);
        bool ret=pix.load(":/PVZ/corn1.png");

        if(!ret)
        {
            QString str=QString("%1 图片加载失败").arg(":/PVZ/corn1.png");
            qDebug()<< str;
        }


        bool ret1=secondpix.load(":/PVZ/corn.png");

        if(!ret1)
        {
            QString str=QString("%1 图片加载失败").arg(":/PVZ/corn.png");
            qDebug()<< str;

        }



        break;
    }
    case Peashooter:
    {
        bool ret=pix.load(":/PVZ/pea.png");

        if(!ret)
        {
            QString str=QString("%1 图片加载失败").arg(":/PVZ/pea.png");
            qDebug()<< str;

        }
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
    }
        break;
    default:
        break;
    }

    //设定图片大小
    this ->setImgSize(100,100);

    //设置不规则图片样式

    this->setStyleSheet("QPushButton{border:0px ; }");

    //设置图片
    this->setIcon(pix);

    //设置图片大小
}


//被激活的植物来搜索僵尸位置，判断是否发动攻击
void PlantAndPosition::ActivePlantSearchDistance( PlantAndPosition* plant ,zooomb * zb[],int num,int distance,int time)
{

    for (int i=0;i<num;i++)
    {

        if(zb[i])
        {
            if(zb[i]!=NULL&&plant->JudgeDistance(zb[i]->GetPoint(),distance))
            {
                plant->MyBullet->Movemap(QRect( plant->GetCoordinate().x(),plant->GetCoordinate().y(),
                                                plant->GetCoordinate().x(),plant->GetCoordinate().y()),
                                         QRect( zb[i]->GetPoint().x(),zb[i]->GetPoint().y(),
                                                zb[i]->GetPoint().x(),zb[i]->GetPoint().y()),time,zb[i]);
            }


        }
    }
}


int PlantAndPosition::GetPlantId()
{
    return PlantID;
}

bool PlantAndPosition::JudgeDistance(QPoint ZoombPoint, int distance)
{
    if (((ZoombPoint.x()-coordinate.x())*(ZoombPoint.x()-coordinate.x())+
         (ZoombPoint.y()-coordinate.y())*(ZoombPoint.y()-coordinate.y()))<=distance*distance)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PlantAndPosition::SetState(int a,int b,int c,int d,int e)
{
    SelectNumber=a;
    row =b;
    lin =c;
    MoveStatex = d;
    MoveStatey = e;
}

//设置植物坐标
void PlantAndPosition::SetCoordinate(int x,int y)
{
    coordinate=QPoint(x,y);
}

//得到植物的坐标
QPoint PlantAndPosition::GetCoordinate()
{
    return  coordinate;
}

int PlantAndPosition::GetX()
{
    return MoveStatex;
}

int PlantAndPosition::GetY()
{
    return MoveStatey;
}

//改变植物状态
void PlantAndPosition::ChangPlantState( )
{
    if(this->IsPlant==false)

    {this->IsPlant  =true;
        PlantAndPosition::ActiveNumber1++;
    }
//    qDebug()<<"塔基里面的植物种植改变函数运行变成"<< PlantAndPosition::IsPlant;
}

//改变选择状态
void PlantAndPosition::ChangSelectState( )
{
    if(PlantAndPosition::IsSelect==true)
    {
        PlantAndPosition::IsSelect  = false;
    }
    else
    {
        PlantAndPosition::IsSelect = true;
    }
//    qDebug()<<"塔基里面的选择状态改变函数运行变成"<< PlantAndPosition::IsSelect;
}

bool PlantAndPosition::PlantState()
{
    return this->IsPlant;
}
