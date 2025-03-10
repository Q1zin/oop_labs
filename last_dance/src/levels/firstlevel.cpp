#include <QGraphicsScene>
#include <QDebug>
#include <QString>
#include "include/levels/firstlevel.h"
#include "include/textures/itexture.h"
#include "include/structs/datatexture.h"

std::vector<std::pair<QString, dataTexture>> FirstLevel::getTextures() {
    std::vector<std::pair<QString, dataTexture>> textures;

    textures.emplace_back("regular", dataTexture{QPoint(160, 720 - 35), QSize(40, 35)});
    textures.emplace_back("regular", dataTexture{QPoint(120, 720 - 50), QSize(40, 50)});
    textures.emplace_back("regular", dataTexture{QPoint(200, 720 - 20), QSize(1080, 20)});

    textures.emplace_back("regular", dataTexture{QPoint(220, 600), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(620, 600), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(420, 520), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(720, 450), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(420, 380), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(120, 310), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(670, 220), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(320, 220), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(0, 150), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(670, 120), QSize(200, 20)});
    textures.emplace_back("regular", dataTexture{QPoint(900, 76), QSize(200, 20)});

    textures.emplace_back("coin", dataTexture{QPoint(195, 250), QSize(0, 0)});
    textures.emplace_back("coin", dataTexture{QPoint(750, 160), QSize(0, 0)});
    textures.emplace_back("coin", dataTexture{QPoint(795, 390), QSize(0, 0)});

    return textures;
}

std::vector<std::pair<EnemyType, dataEnemy> > FirstLevel::getEnemys() {
    return {};
}
