#include <QGraphicsScene>
#include <QTimer>
#include <QUrl>
#include <QPixmap>
#include "include/levels/thirdlevel.h"
#include "include/entities/player.h"
#include "include/entities/enemy.h"
#include "include/levels/levelssettings.h"
#include "include/managers/texturefactory.h"

#define TIME_RESET_MOB 5000

struct TextureData {
    QString type;
    QPoint position;
    QSize size;
};

struct EnemyData {
    QPoint position;
    QSize size;
    int hp;
    QString img;
};

void ThirdLevel::loadLevel(QGraphicsScene *scene, Player *player)
{
    std::vector<TextureData> textures = {
        {"regular", QPoint(160, scene->height() - 35), QSize(40, 35)},
        {"regular", QPoint(120, scene->height() - 50), QSize(40, 50)},
        {"regular", QPoint(200, scene->height() - 20), QSize(1080, 20)},
        {"regular", QPoint(260, 610), QSize(200, 20)},
        {"regular", QPoint(1080, 635), QSize(200, 20)},
        {"regular", QPoint(880, 536), QSize(200, 20)},
        {"regular", QPoint(590, 446), QSize(200, 20)},
        {"regular", QPoint(590, 356), QSize(200, 20)},
        {"regular", QPoint(590, 266), QSize(200, 20)},
        {"regular", QPoint(230, 266), QSize(200, 20)},
        {"regular", QPoint(230, 176), QSize(200, 20)},
        {"regular", QPoint(540, 116), QSize(200, 20)},
        {"regular", QPoint(890, 140), QSize(200, 20)},
        {"coin", QPoint(305, 206), QSize()},
        {"coin", QPoint(665, 206), QSize()},
        {"coin", QPoint(965, 84), QSize()}
    };

    std::vector<EnemyData> enemies = {
        {QPoint(980, 650), QSize(50, 50), 1, ":/img/enemy_type_1.png"},
        {QPoint(690, 395), QSize(50, 50), 1, ":/img/enemy_type_1.png"},
        {QPoint(305, 125), QSize(50, 50), 10, ":/img/enemy_type_2.png"},
        {QPoint(1215, 24), QSize(50, 50), 10, ":/img/enemy_type_2.png"}
    };

    for (const auto& textureData : textures) {
        scene->addItem(TextureFactory::create(textureData.type, textureData.position, textureData.size));
    }

    for (const auto& enemyData : enemies) {
        scene->addItem(new Enemy(scene, enemyData.position, enemyData.size, enemyData.hp, enemyData.img, player));
    }

    enemySpawnTimer = new QTimer(0);
    QObject::connect(enemySpawnTimer, &QTimer::timeout, enemySpawnTimer, [scene, player]() {
        scene->addItem(new Enemy(scene, QPoint(615, 0), QSize(50, 50), 1, ":/img/enemy_type_1.png", player));
    });

    enemySpawnTimer->start(TIME_RESET_MOB);
}

QTimer* ThirdLevel::getTimer()
{
    return enemySpawnTimer;
}
