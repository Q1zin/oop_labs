#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QTimer>
#include "include/textures/itexture.h"
#include "include/structs/datatexture.h"
#include "include/structs/dataenemy.h"

class Level {
protected:
    int bestTime;
public:
    Level();
    virtual ~Level() = default;

    virtual std::vector<std::pair<QString, dataTexture>> getTextures() = 0;
    virtual std::vector<std::pair<EnemyType, dataEnemy>> getEnemys() = 0;
    int getBestTime() const;
    void setBestTime(int time);
};

#endif // LEVEL_H
