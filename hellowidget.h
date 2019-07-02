#ifndef HELLOWIDGET_H
#define HELLOWIDGET_H

#include <QWidget>
#include<QPushButton>
#include"toolwidget.h"
#include"play.h"
class HelloWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton b1,b2,b3;
    toolwidget w1;
    play w2;
public:
    HelloWidget(QWidget *parent = 0);
    ~HelloWidget();
    void changetool();
    void dealtool();
    void changeplay();
    void dealplay();
};

#endif // WIDGET_H
