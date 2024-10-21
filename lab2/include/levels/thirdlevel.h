#ifndef THIRDLEVEL_H
#define THIRDLEVEL_H

#include <QGraphicsScene>
#include "include/levels/level.h"
#include "include/entities/player.h"

class ThirdLevel : public Level {
public:
    void loadLevel(QGraphicsScene* scene, Player* player = nullptr) override;
    QTimer* getTimer() override;

private:
    QTimer* enemySpawnTimer;
};
#endif // THIRDLEVEL_H
