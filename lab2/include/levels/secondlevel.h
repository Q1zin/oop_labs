#ifndef SECONDLEVEL_H
#define SECONDLEVEL_H

#include <QGraphicsScene>
#include "include/levels/level.h"
#include "include/entities/player.h"

class SecondLevel : public Level {
public:
    void loadLevel(QGraphicsScene* scene, Player* player = nullptr) override;
};

#endif // SECONDLEVEL_H
