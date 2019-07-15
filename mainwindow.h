#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<chooselevelscene.h>
#include<settingmenu.h>
#include<QMenuBar>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //绘图事件
    void paintEvent(QPaintEvent *);
    //这个是开始菜单，指向两个窗口：选择关卡和设置
    chooselevelscene *choose;
    SettingMenu * setting;

private:

};

#endif // MAINWINDOW_H
