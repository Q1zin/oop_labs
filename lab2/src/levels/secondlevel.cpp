#include <QGraphicsScene>
#include "include/levels/secondlevel.h"
#include "include/entities/player.h"
#include "include/entities/enemy.h"
#include "include/levels/levelssettings.h"
#include "include/managers/texturefactory.h"

void SecondLevel::loadLevel(QGraphicsScene *scene, Player *player)
{
    scene->addItem(TextureFactory::create("regular", 40, 35, 160, scene->height() - 35));
    scene->addItem(TextureFactory::create("regular", 40, 50, 120, scene->height() - 50));
    scene->addItem(TextureFactory::create("regular", 1080, 20, 200, scene->height() - 20));

    scene->addItem(TextureFactory::create("regular", 200, 20, 50, 415));
    scene->addItem(TextureFactory::create("regular", 200, 20, 110, 270));
    scene->addItem(TextureFactory::create("regular", 200, 20, 0, 170));
    scene->addItem(TextureFactory::create("regular", 200, 20, 420, 340));
    scene->addItem(TextureFactory::create("regular", 200, 20, 465, 216));
    scene->addItem(TextureFactory::create("regular", 200, 20, 710, 170));
    scene->addItem(TextureFactory::create("regular", 200, 20, 800, 340));
    scene->addItem(TextureFactory::create("regular", 200, 20, 940, 110));

    scene->addItem(TextureFactory::create("regular", 280, 80, 1000, 460));
    scene->addItem(TextureFactory::create("regular", 370, 80, 910, 540));
    scene->addItem(TextureFactory::create("regular", 560, 80, 720, 620));

    scene->addItem(TextureFactory::create("coin", 0, 0, 75, 110));
    scene->addItem(TextureFactory::create("coin", 0, 0, 125, 355));
    scene->addItem(TextureFactory::create("coin", 0, 0, 1205, 400));

    scene->addItem(new Enemy(scene, 380, 650, 50, 50, 1, "/Users/mir/Realm_of_Rebirth/assets/img/enemy_type_1.png", player));
    scene->addItem(new Enemy(scene, 790, 570, 50, 50, 1, "/Users/mir/Realm_of_Rebirth/assets/img/enemy_type_1.png", player));
    scene->addItem(new Enemy(scene, 1130, 410, 50, 50, 10, "/Users/mir/Realm_of_Rebirth/assets/img/enemy_type_2.png", player));
    scene->addItem(new Enemy(scene, 1215, 25, 50, 50, 10, "/Users/mir/Realm_of_Rebirth/assets/img/enemy_type_2.png", player));
}
