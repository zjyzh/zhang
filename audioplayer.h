#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

class QMediaPlayer;
//这个音频类的音频载入有问题，所以连带设置菜单一块都无法设置，解决时间不足了

enum SoundType
{
	TowerPlaceSound,		// 放塔时的声音
	LifeLoseSound,			// 基地费血时的声音
	LaserShootSound,		// 打中敌人时的生意
	EnemyDestorySound		// 敌人升天时的声音
};

class AudioPlayer : public QObject
{
public:
	explicit AudioPlayer(QObject *parent = 0);

	void startBGM();
	void playSound(SoundType soundType);

private:
	QMediaPlayer *m_backgroundMusic; // 只用来播放背景音乐
};


#endif // AUDIOPLAYER_H
