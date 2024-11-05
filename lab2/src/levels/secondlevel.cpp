#include <QGraphicsScene>
#include "include/levels/secondlevel.h"
#include "include/entities/player.h"
#include "include/entities/enemy.h"
#include "include/levels/levelssettings.h"
#include "include/managers/texturefactory.h"

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

void SecondLevel::loadLevel(QGraphicsScene *scene, Player *player) {
    std::vector<TextureData> textures = {
        {"regular", QPoint(160, scene->height() - 35), QSize(40, 35)},
        {"regular", QPoint(120, scene->height() - 50), QSize(40, 50)},
        {"regular", QPoint(200, scene->height() - 20), QSize(1080, 20)},
        {"regular", QPoint(50, 415), QSize(200, 20)},
        {"regular", QPoint(110, 270), QSize(200, 20)},
        {"regular", QPoint(0, 170), QSize(200, 20)},
        {"regular", QPoint(420, 340), QSize(200, 20)},
        {"regular", QPoint(465, 216), QSize(200, 20)},
        {"regular", QPoint(710, 170), QSize(200, 20)},
        {"regular", QPoint(800, 340), QSize(200, 20)},
        {"regular", QPoint(940, 110), QSize(200, 20)},
        {"regular", QPoint(1000, 460), QSize(280, 80)},
        {"regular", QPoint(910, 540), QSize(370, 80)},
        {"regular", QPoint(720, 620), QSize(560, 80)},
        {"coin", QPoint(75, 110)},  // Размер для монет не указан, предполагается по умолчанию
        {"coin", QPoint(125, 355)},
        {"coin", QPoint(1205, 400)}
    };

    std::vector<EnemyData> enemies = {
        {QPoint(380, 650), QSize(50, 50), 1, ":/img/enemy_type_1.png"},
        {QPoint(790, 570), QSize(50, 50), 1, ":/img/enemy_type_1.png"},
        {QPoint(1130, 410), QSize(50, 50), 10, ":/img/enemy_type_2.png"},
        {QPoint(1215, 25), QSize(50, 50), 10, ":/img/enemy_type_2.png"}
    };

    for (const auto& textureData : textures) {
        ITexture* block = TextureFactory::create(textureData.type, textureData.position, textureData.size);
        texturesObj.push_back(block);
        block->setZValue(500);
        scene->addItem(block);
    }

    for (const auto& enemyData : enemies) {
        Enemy* enemy = new Enemy(scene, enemyData.position, enemyData.size, enemyData.hp, enemyData.img, player);
        enemyObj.push_back(enemy);
        enemy->setZValue(500);
        scene->addItem(enemy);
    }
}

void SecondLevel::deleteUi() {
    for (const auto& textureData : texturesObj) {
        if (textureData) delete textureData;
    }
    texturesObj.resize(0);

    for (const auto& enemyData : enemyObj) {
        if (enemyData) {
            delete enemyData;
        }
    }
    enemyObj.resize(0);
}
