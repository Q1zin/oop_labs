#include <QMediaPlayer>
#include <QAudioOutput>
#include <memory>
#include "include/managers/soundmanager.h"

SoundManager::SoundManager() : QObject(0) {
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

void SoundManager::setSound(const QString& sound) {
    if (sound == "menu") {
        playSound("qrc:/music/music_menu.mp3", QMediaPlayer::Infinite, musicPlayer.get());
    } else if (sound == "game") {
        playSound("qrc:/music/music_game.mp3", QMediaPlayer::Infinite, musicPlayer.get());
    } else if (sound == "win") {
        playSound("qrc:/music/music_win.wav", 1, musicPlayer.get());
    } else if (sound == "game_over") {
        playSound("qrc:/music/music_game_over.mp3", 1, musicPlayer.get());
    } else if (sound == "collected_coin") {
        playSound("qrc:/music/collected_coin.mp3", 1, soundEffectCoin.get());
    } else if (sound == "shot") {
        playSound("qrc:/music/laser.mp3", 1, soundEffectShot.get());
    }
}

void SoundManager::setSoundCoin() {
    setSound("collected_coin");
}

void SoundManager::setSoundShot() {
    setSound("shot");
}

void SoundManager::playSound(const QString &source, int loops, QMediaPlayer *musicPlayer) {
    musicPlayer->stop();
    musicPlayer->setSource(QUrl(source));
    musicPlayer->setLoops(loops);
    musicPlayer->play();
}
