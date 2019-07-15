#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include<QPainter>
#include<playsence.h>
//这个是选择关卡界面
class chooselevelscene : public QMainWindow
{
    Q_OBJECT

public:
    explicit chooselevelscene(QWidget *parent = nullptr);

    //重写绘图事件
     void paintEvent(QPaintEvent *);

     //这个是游戏场景的指针，指向开始游戏的场景
     playSence * playsence;

signals:
     //这个是返回按钮的信号
     void back();

public slots:


     };


#endif // CHOOSELEVELSCENE_H
