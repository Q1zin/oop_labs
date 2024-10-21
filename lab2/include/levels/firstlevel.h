#ifndef FIRSTLEVEL_H
#define FIRSTLEVEL_H

#include <QGraphicsScene>
#include "include/levels/level.h"
#include "include/entities/player.h"

class FirstLevel : public Level {
public:
    void loadLevel(QGraphicsScene* scene, Player* player = nullptr) override;
};

#endif // FIRSTLEVEL_H
