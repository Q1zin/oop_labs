#ifndef SECONDLEVEL_H
#define SECONDLEVEL_H

#include <QGraphicsScene>
#include "include/textures/itexture.h"
#include "include/entities/enemy.h"
#include "include/levels/level.h"
#include "include/entities/player.h"

class SecondLevel : public Level {
public:
    void loadLevel(QGraphicsScene* scene, TextureFactory<ITexture, QString> textureFactory, Player* player = nullptr) override;
    void deleteUi() override;
private:
    std::vector<ITexture*> texturesObj;
    std::vector<Enemy* > enemyObj;
};

#endif // SECONDLEVEL_H
