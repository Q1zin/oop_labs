#include <QGraphicsScene>
#include "include/levels/firstlevel.h"
#include "include/entities/player.h"
#include "include/managers/texturefactory.h"

void FirstLevel::loadLevel(QGraphicsScene *scene, Player* player) {
    scene->addItem(TextureFactory::create("regular", 40, 35, 160, scene->height() - 35));
    scene->addItem(TextureFactory::create("regular", 40, 50, 120, scene->height() - 50));
    scene->addItem(TextureFactory::create("regular", 1080, 20, 200, scene->height() - 20));

    scene->addItem(TextureFactory::create("regular", 200, 20, 220, 600));
    scene->addItem(TextureFactory::create("regular", 200, 20, 620, 600));
    scene->addItem(TextureFactory::create("regular", 200, 20, 420, 520));
    scene->addItem(TextureFactory::create("regular", 200, 20, 720, 450));
    scene->addItem(TextureFactory::create("regular", 200, 20, 420, 380));
    scene->addItem(TextureFactory::create("regular", 200, 20, 120, 310));
    scene->addItem(TextureFactory::create("regular", 200, 20, 670, 220));
    scene->addItem(TextureFactory::create("regular", 200, 20, 320, 220));
    scene->addItem(TextureFactory::create("regular", 200, 20, 0, 150));
    scene->addItem(TextureFactory::create("regular", 200, 20, 670, 120));
    scene->addItem(TextureFactory::create("regular", 200, 20, 900, 76));

    scene->addItem(TextureFactory::create("coin", 0, 0, 195, 250));
    scene->addItem(TextureFactory::create("coin", 0, 0, 750, 160));
    scene->addItem(TextureFactory::create("coin", 0, 0, 795, 390));
}
