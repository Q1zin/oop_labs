#ifndef LEVELSSETTINGS_H
#define LEVELSSETTINGS_H

#include <vector>
#include <QGraphicsScene>
#include "include/levels/level.h"
#include "include/managers/scoremanager.h"

class LevelsSettings {
public:
    LevelsSettings();

    void initializeLevels();
    void loadLevel(int lvl, QGraphicsScene* scene, Player* player = nullptr);
    void updateBestTime(int lvl, int time);
    int getLevelsCount() const;
    int getBestTime(int lvl) const;
    void pauseEnemySpawning(int lvl);
    void resumeEnemySpawning(int lvl);

private:
    std::vector<std::unique_ptr<Level>> levels;
    ScoreManager* scoreManager;
    QTimer* getTimerLvl(int lvl);
    int remainingTime;
};

#endif // LEVELSSETTINGS_H
