#include <QGraphicsScene>
#include "include/levels/secondlevel.h"
#include "include/entities/player.h"
#include "include/entities/enemy.h"
#include "include/levels/levelssettings.h"
#include "include/managers/texturefactory.h"
#include "include/managers/enemyfactory.h"

struct TextureData {
    QString type;
    QPoint position;
    QSize size;
};

struct EnemyData {
    EnemyType type;
    QPoint position;
};

void SecondLevel::loadLevel(QGraphicsScene* scene, TextureFactory<ITexture, QString> textureFactory, Player* player) {
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
        {"coin", QPoint(75, 110), QSize(0, 0)},
        {"coin", QPoint(125, 355), QSize(0, 0)},
        {"coin", QPoint(1205, 400), QSize(0, 0)}
    };

    std::vector<EnemyData> enemies = {
        {EASY, QPoint(380, 650)},
        {EASY, QPoint(790, 570)},
        {MEDIUM, QPoint(1130, 410)},
        {HARD, QPoint(1215, 25)}
    };

    for (const auto& textureData : textures) {
        ITexture* block = textureFactory.Create(textureData.type, textureData.position, textureData.size);;
        texturesObj.push_back(block);
        block->setZValue(500);
        scene->addItem(block);
    }

    for (const auto& enemyData : enemies) {
        Enemy* enemy = EnemyFactory::create(enemyData.type, scene, enemyData.position, player);
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
