#include <vector>
#include <QGraphicsScene>
#include <QStandardPaths>
#include "include/levels/levelssettings.h"
#include "include/entities/player.h"
#include "include/levels/firstlevel.h"
#include "include/levels/secondlevel.h"
#include "include/levels/thirdlevel.h"

LevelsSettings::LevelsSettings()
{
    initializeLevels();
    // scoreManager = new ScoreManager(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/best_times.json", getLevelsCount());
    scoreManager = new ScoreManager("/Users/mir/Realm_of_Rebirth/best_times.json", getLevelsCount());
    if (scoreManager->getReadStatus()) {
        for (int i = 1; i <= getLevelsCount(); i++) {
            levels[i - 1]->setBestTime(scoreManager->getBestScore(i));
        }
    }
}

void LevelsSettings::initializeLevels() {
    levels.push_back(std::make_unique<FirstLevel>());
    levels.push_back(std::make_unique<SecondLevel>());
    levels.push_back(std::make_unique<ThirdLevel>());
}

void LevelsSettings::loadLevel(int lvl, QGraphicsScene *scene, Player* player) {
    if (lvl - 1 < 0 && lvl - 1 >= levels.size()) return;
    levels[lvl - 1]->loadLevel(scene, player);
    remainingTime = 0;
}

void LevelsSettings::updateBestTime(int lvl, int time) {
    if (lvl - 1 < 0 && lvl - 1 >= levels.size()) return;
    if (levels[lvl - 1]->getBestTime() == 0 || time < levels[lvl - 1]->getBestTime()) {
        levels[lvl - 1]->setBestTime(time);
        scoreManager->saveBestScore(lvl, time);
    }
}

int LevelsSettings::getLevelsCount() const {
    return levels.size();
}

int LevelsSettings::getBestTime(int lvl) const {
    if (lvl - 1 >= 0 && lvl - 1 < levels.size()) {
        return levels[lvl - 1]->getBestTime();
    }

    return 0;
}

QTimer* LevelsSettings::getTimerLvl(int lvl) {
    if (lvl - 1 < 0 && lvl - 1 >= levels.size()) return nullptr;
    return levels[lvl - 1]->getTimer();
}

void LevelsSettings::pauseEnemySpawning(int lvl) {
    QTimer* enemySpawnTimer = getTimerLvl(lvl);
    if (!enemySpawnTimer) return;
    remainingTime = enemySpawnTimer->remainingTime();
    enemySpawnTimer->stop();
}

void LevelsSettings::resumeEnemySpawning(int lvl) {
    QTimer* enemySpawnTimer = getTimerLvl(lvl);
    if (!enemySpawnTimer) return;
    if (remainingTime > 0) {
        enemySpawnTimer->start(remainingTime);
    } else {
        enemySpawnTimer->start(5000);
    }
}
