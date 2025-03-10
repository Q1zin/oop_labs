#include <QGraphicsScene>
#include <QDebug>
#include "include/levels/secondlevel.h"
#include "include/textures/itexture.h"
#include "include/structs/datatexture.h"

std::vector<std::pair<QString, dataTexture>> SecondLevel::getTextures() {
    std::vector<std::pair<QString, dataTexture>> textures;

    textures.emplace_back("regular", dataTexture{QPoint(160, 720 - 35), QSize(40, 35)});
    textures.emplace_back("regular", dataTexture{QPoint(120, 720 - 50), QSize(40, 50)});
    textures.emplace_back("regular", dataTexture{QPoint(200, 720 - 20), QSize(1080, 20)});

    textures.emplace_back("regular", dataTexture{QPoint(50, 415), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(110, 270), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(0, 170), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(420, 340), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(465, 216), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(710, 170), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(800, 340), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(940, 110), QSize(200, 20)});

    textures.emplace_back("regular", dataTexture{QPoint(1000, 460), QSize(280, 80)});
    textures.emplace_back("regular", dataTexture{QPoint(910, 540), QSize(370, 80)});
    textures.emplace_back("regular", dataTexture{QPoint(720, 620), QSize(560, 80)});

    textures.emplace_back("coin", dataTexture{QPoint(75, 110), QSize(0, 0)});
    textures.emplace_back("coin", dataTexture{QPoint(125, 355), QSize(0, 0)});
    textures.emplace_back("coin", dataTexture{QPoint(1205, 400), QSize(0, 0)});

    return textures;
}

std::vector<std::pair<EnemyType, dataEnemy> > SecondLevel::getEnemys() {
    std::vector<std::pair<EnemyType, dataEnemy>> enemy;
    enemy.emplace_back(EASY, dataEnemy{QPointF(380, 650)});
    enemy.emplace_back(EASY, dataEnemy{QPointF(790, 570)});
    enemy.emplace_back(MEDIUM, dataEnemy{QPointF(1130, 410)});
    enemy.emplace_back(HARD, dataEnemy{QPointF(1215, 25)});

    return enemy;
}
