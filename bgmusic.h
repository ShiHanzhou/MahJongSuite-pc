#ifndef BGMUSIC_H
#define BGMUSIC_H

#include <QThread>
//#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QtCore/QCoreApplication>
#include <QtMultimedia/QMediaPlayer>

class bgmusic : public QThread
{
    Q_OBJECT

public:
    bgmusic();
    void run() override;

private:
    QMediaPlayer* player;
    QMediaPlaylist* playerList;
    void initStatus(QMediaPlayer::MediaStatus status); // 槽函数 监听QMediaPlayer::mediaStatusChanged信号
};

#endif // BGMUSIC_H

