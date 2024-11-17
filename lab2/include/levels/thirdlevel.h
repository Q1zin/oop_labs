#ifndef THIRDLEVEL_H
#define THIRDLEVEL_H

#include <QGraphicsScene>
#include "include/textures/itexture.h"
#include "include/entities/enemy.h"
#include "include/levels/level.h"
#include "include/entities/player.h"

class ThirdLevel : public Level {
public:
    void loadLevel(QGraphicsScene* scene, TextureFactory<ITexture, QString> textureFactory, Player* player = nullptr) override;
    QTimer* getTimer() override;
    void deleteUi() override;

private:
    QTimer* enemySpawnTimer;
    std::vector<ITexture*> texturesObj;
    std::vector<Enemy* > enemyObj;
};
#endif // THIRDLEVEL_H
