#include <vector>
#include <QGraphicsScene>
#include <QStandardPaths>
#include "include/levels/levelssettings.h"
#include "include/levels/firstlevel.h"
#include "include/levels/secondlevel.h"
#include "include/levels/thirdlevel.h"
#include "include/structs/datatexture.h"

LevelsSettings::LevelsSettings(QObject *parent) : QObject(parent)  {
    initializeLevels();
    scoreManager.reset(new ScoreManager("/Users/mir/Documents/last_dance/best_time.json", getLevelsCount()));
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

std::vector<std::pair<QString, dataTexture>> LevelsSettings::getTexturesLevel(int lvl) {
    size_t index = static_cast<size_t>(lvl - 1);
    if (lvl - 1 < 0 && index >= levels.size()) return {};
    return levels[lvl - 1]->getTextures();
}

std::vector<std::pair<EnemyType, dataEnemy>> LevelsSettings::getEnemysLevel(int lvl) {
    size_t index = static_cast<size_t>(lvl - 1);
    if (lvl - 1 < 0 && index >= levels.size()) return {};
    return levels[lvl - 1]->getEnemys();
}

void LevelsSettings::updateBestTime(int lvl, int time) {
    size_t index = static_cast<size_t>(lvl - 1);
    if (lvl - 1 < 0 && index >= levels.size()) return;
    if (levels[lvl - 1]->getBestTime() == 0 || time < levels[lvl - 1]->getBestTime()) {
        levels[lvl - 1]->setBestTime(time);
        scoreManager->saveBestScore(lvl, time);
    }
}

int LevelsSettings::getLevelsCount() const {
    return levels.size();
}

int LevelsSettings::getBestTime(int lvl) const {
    size_t index = static_cast<size_t>(lvl - 1);
    if (lvl - 1 >= 0 && index < levels.size()) {
        return levels[lvl - 1]->getBestTime();
    }

    return 0;
}
