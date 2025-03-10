#ifndef THIRDLEVEL_H
#define THIRDLEVEL_H

#include <QGraphicsScene>
#include "include/levels/level.h"
#include "include/textures/itexture.h"
#include "include/structs/datatexture.h"

class ThirdLevel : public Level {
public:
    std::vector<std::pair<QString, dataTexture>> getTextures() override;
    std::vector<std::pair<EnemyType, dataEnemy>> getEnemys() override;
};

#endif // THIRDLEVEL_H
