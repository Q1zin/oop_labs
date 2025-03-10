#include "include/managers/soundmanager.h"

SoundManager::SoundManager(QObject *parent) : QObject(parent), currentMusicType(SoundType::Menu) {
    initializeSounds();
}

void SoundManager::initializeSounds() {
    soundInfos = {
        {SoundType::Menu, {QUrl("qrc:/music/music_menu.mp3"), QMediaPlayer::Infinite}},
        {SoundType::Game, {QUrl("qrc:/music/music_game.mp3"), QMediaPlayer::Infinite}},
        {SoundType::Win, {QUrl("qrc:/music/music_win.mp3"), 1}},
        {SoundType::GameOver, {QUrl("qrc:/music/music_game_over.mp3"), 1}},
        {SoundType::CollectedCoin, {QUrl("qrc:/music/collected_coin.mp3"), 1}},
        {SoundType::Shot, {QUrl("qrc:/music/laser.mp3"), 1}}
    };

    for (auto it = soundInfos.constBegin(); it != soundInfos.constEnd(); ++it) {
        auto player = std::make_unique<QMediaPlayer>(this);
        auto output = std::make_unique<QAudioOutput>(this);
        output->setVolume(50);
        player->setAudioOutput(output.get());

        players.emplace(it.key(), std::move(player));
        outputs.emplace(it.key(), std::move(output));
    }
}

void SoundManager::stopCurrentMusic() {
    auto it = players.find(currentMusicType);
    if (it != players.end()) {
        it->second->stop();
    }
}

void SoundManager::playSound(SoundType type) {
    auto playerIt = players.find(type);
    if (playerIt != players.end()) {
        if (type == SoundType::Menu || type == SoundType::Game || type == SoundType::Win || type == SoundType::GameOver) {
            stopCurrentMusic();
            currentMusicType = type;
        }

        auto& player = playerIt->second;
        auto soundInfo = soundInfos.value(type);
        player->stop();
        player->setSource(soundInfo.source);
        player->setLoops(soundInfo.loops);
        player->play();
    }
}

void SoundManager::setVolume(SoundType type, int volume) {
    auto outputIt = outputs.find(type);
    if (outputIt != outputs.end()) {
        outputIt->second->setVolume(volume);
    }
}

void SoundManager::stopAll() {
    for (auto& playerPair : players) {
        playerPair.second->stop();
    }
}
