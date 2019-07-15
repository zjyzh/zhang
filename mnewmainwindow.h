#ifndef MNEWMAINWINDOW_H
#define MNEWMAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"

namespace Ui {
class mnewMainWindow;
}

class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;

class mnewMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mnewMainWindow(QWidget *parent = 0);
    ~mnewMainWindow();

    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void awardGold(int gold);

    AudioPlayer* audioPlayer() const;
    QList<Enemy *> enemyList() const;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void updateMap();
    void gameStart();

private:
    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();

private:
    Ui::mnewMainWindow *		ui;
    int						m_waves;//-----------敌人波数
    int						m_playerHp;//-----------基地血量
    int						m_playrGold;//----------金钱数
    bool					m_gameEnded;
    bool					m_gameWin;
    AudioPlayer *			m_audioPlayer;//--------音乐管理
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList;//-----------塔基管理
    QList<Tower *>			m_towersList;//-----------塔管理
    QList<WayPoint *>		m_wayPointsList;//-----------航线航点管理
    QList<Enemy *>			m_enemyList;//--------敌人管理
    QList<Bullet *>			m_bulletList;//----------子弹管理
};


#endif // MNEWMAINWINDOW_H
