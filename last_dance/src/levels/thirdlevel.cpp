#include <QGraphicsScene>
#include <QDebug>
#include "include/levels/thirdlevel.h"
#include "include/textures/itexture.h"
#include "include/structs/datatexture.h"

std::vector<std::pair<QString, dataTexture>> ThirdLevel::getTextures() {
    std::vector<std::pair<QString, dataTexture>> textures;

    textures.emplace_back("regular", dataTexture{QPoint(160, 720 - 35), QSize(40, 35)});
    textures.emplace_back("regular", dataTexture{QPoint(120, 720 - 50), QSize(40, 50)});
    textures.emplace_back("regular", dataTexture{QPoint(200, 720 - 20), QSize(1080, 20)});

    textures.emplace_back("regular", dataTexture{QPoint(260, 610), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(1080, 635), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(880, 536), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(590, 446), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(590, 356), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(590, 266), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(230, 266), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(230, 176), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(540, 116), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(890, 140), QSize(200, 20)});

    textures.emplace_back("coin", dataTexture{QPoint(305, 206), QSize(0, 0)});
    textures.emplace_back("coin", dataTexture{QPoint(665, 206), QSize(0, 0)});
    textures.emplace_back("coin", dataTexture{QPoint(965, 84), QSize(0, 0)});

    return textures;
}

std::vector<std::pair<EnemyType, dataEnemy> > ThirdLevel::getEnemys() {
    std::vector<std::pair<EnemyType, dataEnemy>> enemy;
    enemy.emplace_back(EASY, dataEnemy{QPointF(980, 650)});
    enemy.emplace_back(MEDIUM, dataEnemy{QPointF(690, 395)});
    enemy.emplace_back(HARD, dataEnemy{QPointF(1215, 24)});

    return enemy;
}
