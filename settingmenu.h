#ifndef SETTINGMENU_H
#define SETTINGMENU_H

#include <QWidget>
#include"PlantAndPosition.h"
class SettingMenu : public QWidget
{
    Q_OBJECT
public:
    //设置菜单还没怎么写
    explicit SettingMenu(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:
    void back();

public slots:
};

#endif // SETTINGMENU_H
