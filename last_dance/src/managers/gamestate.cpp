#include "include/managers/gamestate.h"
#include "include/levels/levelssettings.h"
#include "include/entities/view/playerview.h"

GameState::GameState(QObject* parent) : QObject(parent), levelsSettings(std::make_unique<LevelsSettings>()), 
    currentLevel(1), lvl_count(levelsSettings->getLevelsCount()),count_coins(0), finishIsOpen(false) {}

int GameState::getLevel() const {
    return currentLevel;
}

void GameState::setLevel(int level) {
    if (currentLevel != level) {
        currentLevel = level;
    }

    count_coins = 0;
    finishIsOpen = false;
}

int GameState::getLevelCount() const {
    return lvl_count;
}

void GameState::setLevelCount(int count) {
    lvl_count = count;
}

int GameState::getBestTime(int lvl) const {
    return levelsSettings->getBestTime(lvl);
}

void GameState::updateBestTime(int time) {
    levelsSettings->updateBestTime(getLevel(), time);
}

std::vector<std::pair<QString, dataTexture> > GameState::getTexturesLevel(int lvl) {
    return levelsSettings->getTexturesLevel(lvl);
}

std::vector<std::pair<EnemyType, dataEnemy> > GameState::getEnemysLevel(int lvl) {
    return levelsSettings->getEnemysLevel(lvl);
}

void GameState::collectedСoin() {
    if (++count_coins >= 3 && !finishIsOpen) {
        finishIsOpen = true;
        emit finishOpened();
    }
}
