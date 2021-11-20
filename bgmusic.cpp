#include "bgmusic.h"

bgmusic::bgmusic()
{
    playerList = new QMediaPlaylist();
    player = new QMediaPlayer();
    playerList->addMedia(QUrl("qrc:/music/music/bgm.mp3"));
    playerList->addMedia(QUrl("qrc:/music/music/bgm.mp3")); // 方法一、保证有两个音频（可以相同）被添加
    playerList->setPlaybackMode(QMediaPlaylist::Loop);
    playerList->setCurrentIndex(0);
    player->setPlaylist(playerList);
    player->setVolume(100);
    //player->play();
   // connect(player, &QMediaPlayer::mediaStatusChanged,this,&bgmusic::initStatus);// 方法二 槽函数 监听QMediaPlayer::mediaStatusChanged信号   进行连接
}

void bgmusic::run() {
     player->play();
}

void bgmusic::initStatus(QMediaPlayer::MediaStatus status){
    if(status == QMediaPlayer::EndOfMedia)
      {
          // player->setPosition(0);
          // player->play();
      }
}

