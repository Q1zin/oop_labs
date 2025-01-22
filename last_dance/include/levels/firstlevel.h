#ifndef FIRSTLEVEL_H
#define FIRSTLEVEL_H

#include <QGraphicsScene>
#include "include/levels/level.h"
#include "include/textures/itexture.h"
#include "include/structs/datatexture.h"

class FirstLevel : public Level {
public:
    std::vector<std::pair<QString, dataTexture>> getTextures() override;
    std::vector<std::pair<EnemyType, dataEnemy>> getEnemys() override;
};

#endif // FIRSTLEVEL_H
