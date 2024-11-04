#include <QMediaPlayer>
#include <QAudioOutput>
#include <memory>
#include "include/managers/soundmanager.h"

SoundManager::SoundManager() : QObject(0)
{
    musicPlayer = std::make_unique<QMediaPlayer>();
    musicOutput = std::make_unique<QAudioOutput>();
    musicOutput->setVolume(50);
    musicPlayer->setAudioOutput(musicOutput.get());
    musicPlayer->setLoops(QMediaPlayer::Infinite);

    soundEffectCoin = std::make_unique<QMediaPlayer>();
    soundEffectOutputCoin = std::make_unique<QAudioOutput>();
    soundEffectOutputCoin->setVolume(50);
    soundEffectCoin->setAudioOutput(soundEffectOutputCoin.get());

    soundEffectShot = std::make_unique<QMediaPlayer>();
    soundEffectOutputShot = std::make_unique<QAudioOutput>();
    soundEffectOutputShot->setVolume(50);
    soundEffectShot->setAudioOutput(soundEffectOutputShot.get());
}

SoundManager::~SoundManager() {}

void SoundManager::setSound(const QString& sound)
{
    if (sound == "menu") {
        musicPlayer->stop();
        musicPlayer->setSource(QUrl("qrc:/music/music_menu.mp3"));
        musicPlayer->setLoops(QMediaPlayer::Infinite);
        musicPlayer->play();
    } else if (sound == "game") {
        musicPlayer->stop();
        musicPlayer->setSource(QUrl("qrc:/music/music_game.mp3"));
        musicPlayer->setLoops(QMediaPlayer::Infinite);
        musicPlayer->play();
    } else if (sound == "win") {
        musicPlayer->stop();
        musicPlayer->setSource(QUrl("qrc:/music/music_win.wav"));
        musicPlayer->setLoops(1);
        musicPlayer->play();
    } else if (sound == "game_over") {
        musicPlayer->stop();
        musicPlayer->setSource(QUrl("qrc:/music/music_game_over.mp3"));
        musicPlayer->setLoops(1);
        musicPlayer->play();
    } else if (sound == "collected_coin") {
        soundEffectCoin->stop();
        soundEffectCoin->setSource(QUrl("qrc:/music/collected_coin.mp3"));
        soundEffectCoin->setLoops(1);
        soundEffectCoin->play();
    } else if (sound == "shot") {
        soundEffectShot->stop();
        soundEffectShot->setSource(QUrl("qrc:/music/laser.mp3"));
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
