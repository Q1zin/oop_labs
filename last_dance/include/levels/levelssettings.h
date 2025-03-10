#ifndef LEVELSSETTINGS_H
#define LEVELSSETTINGS_H

#include <vector>
#include <QGraphicsScene>
#include "include/levels/level.h"
#include "include/managers/scoremanager.h"
#include "include/structs/datatexture.h"
#include "include/structs/dataenemy.h"

class LevelsSettings : public QObject 
{
    Q_OBJECT
public:
    LevelsSettings(QObject *parent = nullptr);

    void initializeLevels();
    std::vector<std::pair<QString, dataTexture>> getTexturesLevel(int lvl);
    std::vector<std::pair<EnemyType, dataEnemy>> getEnemysLevel(int lvl);
    void updateBestTime(int lvl, int time);
    int getLevelsCount() const;
    int getBestTime(int lvl) const;

private:
    std::vector<std::unique_ptr<Level>> levels;
    QScopedPointer<ScoreManager> scoreManager;
};

#endif // LEVELSSETTINGS_H
