#include <QMediaPlayer>
#include <QAudioOutput>
#include "include/managers/soundmanager.h"

SoundManager::SoundManager() : QObject(0)
{
    musicPlayer = new QMediaPlayer;
    musicOutput = new QAudioOutput;
    musicOutput->setVolume(50);
    musicPlayer->setAudioOutput(musicOutput);
    musicPlayer->setLoops(QMediaPlayer::Infinite);

    soundEffectCoin = new QMediaPlayer;
    soundEffectOutputCoin = new QAudioOutput;
    soundEffectOutputCoin->setVolume(50);
    soundEffectCoin->setAudioOutput(soundEffectOutputCoin);

    soundEffectShot = new QMediaPlayer;
    soundEffectOutputShot = new QAudioOutput;
    soundEffectOutputShot->setVolume(50);
    soundEffectShot->setAudioOutput(soundEffectOutputShot);
}

SoundManager::~SoundManager()
{
    delete musicPlayer;
    delete musicOutput;
    delete soundEffectCoin;
    delete soundEffectOutputCoin;
    delete soundEffectShot;
    delete soundEffectOutputShot;
}

void SoundManager::setSound(const QString& sound)
{
    if (sound == "menu") {
        musicPlayer->stop();
        musicPlayer->setSource(QUrl::fromLocalFile("/Users/mir/Realm_of_Rebirth/assets/music/music_menu.mp3"));
        musicPlayer->setLoops(QMediaPlayer::Infinite);
        musicPlayer->play();
    } else if (sound == "game") {
        musicPlayer->stop();
        musicPlayer->setSource(QUrl::fromLocalFile("/Users/mir/Realm_of_Rebirth/assets/music/music_game.mp3"));
        musicPlayer->setLoops(QMediaPlayer::Infinite);
        musicPlayer->play();
    } else if (sound == "win") {
        musicPlayer->stop();
        musicPlayer->setSource(QUrl::fromLocalFile("/Users/mir/Realm_of_Rebirth/assets/music/music_win.wav"));
        musicPlayer->setLoops(1);
        musicPlayer->play();
    } else if (sound == "game_over") {
        musicPlayer->stop();
        musicPlayer->setSource(QUrl::fromLocalFile("/Users/mir/Realm_of_Rebirth/assets/music/music_game_over.mp3"));
        musicPlayer->setLoops(1);
        musicPlayer->play();
    } else if (sound == "collected_coin") {
        soundEffectCoin->stop();
        soundEffectCoin->setSource(QUrl::fromLocalFile("/Users/mir/Realm_of_Rebirth/assets/music/collected_coin.mp3"));
        soundEffectCoin->setLoops(1);
        soundEffectCoin->play();
    } else if (sound == "shot") {
        soundEffectShot->stop();
        soundEffectShot->setSource(QUrl::fromLocalFile("/Users/mir/Realm_of_Rebirth/assets/music/laser.mp3"));
        soundEffectShot->setLoops(1);
        soundEffectShot->play();
    }
}

void SoundManager::setSoundCoin()
{
    setSound("collected_coin");
}

void SoundManager::setSoundShot()
{
    setSound("shot");
}
