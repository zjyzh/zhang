#ifndef PLAY_H
#define PLAY_H

#include <QWidget>
#include<QPushButton>
class play : public QWidget
{
    Q_OBJECT
public:
    explicit play(QWidget *parent = nullptr);
    void sendSlot();
signals:
    void returnhello();
public slots:
private:
    QPushButton *t1;
};

#endif // PLAY_H
