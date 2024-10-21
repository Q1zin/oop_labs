#include <QGraphicsScene>
#include <QTimer>
#include "include/levels/thirdlevel.h"
#include "include/entities/player.h"
#include "include/entities/enemy.h"
#include "include/levels/levelssettings.h"
#include "include/managers/texturefactory.h"

void ThirdLevel::loadLevel(QGraphicsScene *scene, Player *player)
{
    scene->addItem(TextureFactory::create("regular", 40, 35, 160, scene->height() - 35));
    scene->addItem(TextureFactory::create("regular", 40, 50, 120, scene->height() - 50));
    scene->addItem(TextureFactory::create("regular", 1080, 20, 200, scene->height() - 20));

    scene->addItem(TextureFactory::create("regular", 200, 20, 260, 610));
    scene->addItem(TextureFactory::create("regular", 200, 20, 1080, 635));
    scene->addItem(TextureFactory::create("regular", 200, 20, 880, 536));
    scene->addItem(TextureFactory::create("regular", 200, 20, 590, 446));
    scene->addItem(TextureFactory::create("regular", 200, 20, 590, 356));
    scene->addItem(TextureFactory::create("regular", 200, 20, 590, 266));
    scene->addItem(TextureFactory::create("regular", 200, 20, 230, 266));
    scene->addItem(TextureFactory::create("regular", 200, 20, 230, 176));
    scene->addItem(TextureFactory::create("regular", 200, 20, 540, 116));
    scene->addItem(TextureFactory::create("regular", 200, 20, 890, 140));

    scene->addItem(TextureFactory::create("coin", 0, 0, 305, 206));
    scene->addItem(TextureFactory::create("coin", 0, 0, 665, 206));
    scene->addItem(TextureFactory::create("coin", 0, 0, 965, 84));

    scene->addItem(new Enemy(scene, 980, 650, 50, 50, 1, "/Users/mir/Realm_of_Rebirth/assets/img/enemy_type_1.png", player));
    scene->addItem(new Enemy(scene, 690, 395, 50, 50, 1, "/Users/mir/Realm_of_Rebirth/assets/img/enemy_type_1.png", player));
    scene->addItem(new Enemy(scene, 305, 125, 50, 50, 10, "/Users/mir/Realm_of_Rebirth/assets/img/enemy_type_2.png", player));
    scene->addItem(new Enemy(scene, 1215, 24, 50, 50, 10, "/Users/mir/Realm_of_Rebirth/assets/img/enemy_type_2.png", player));

    enemySpawnTimer = new QTimer(0);
    QObject::connect(enemySpawnTimer, &QTimer::timeout, enemySpawnTimer, [scene, player]() {
        scene->addItem(new Enemy(scene, 615, 0, 50, 50, 1, "/Users/mir/Realm_of_Rebirth/assets/img/enemy_type_1.png", player));
    });

    enemySpawnTimer->start(5000);
}

QTimer* ThirdLevel::getTimer()
{
    return enemySpawnTimer;
}
