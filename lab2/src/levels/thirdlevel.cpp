#include <QGraphicsScene>
#include <QTimer>
#include <QUrl>
#include <QPixmap>
#include "include/levels/thirdlevel.h"
#include "include/entities/player.h"
#include "include/entities/enemy.h"
#include "include/levels/levelssettings.h"
#include "include/managers/texturefactory.h"
#include "include/managers/enemyfactory.h"

#define TIME_RESET_MOB 5000

struct TextureData {
    QString type;
    QPoint position;
    QSize size;
};

struct EnemyData {
    EnemyType type;
    QPoint position;
};

void ThirdLevel::loadLevel(QGraphicsScene *scene, Player *player) {
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
        {EASY, QPoint(980, 650)},
        {EASY, QPoint(690, 395)},
        {MEDIUM,QPoint(305, 125)},
        {MEDIUM, QPoint(1215, 24)}
    };

    for (const auto& textureData : textures) {
        ITexture* block = TextureFactory::create(textureData.type, textureData.position, textureData.size);
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

    enemySpawnTimer = new QTimer(0);
    QObject::connect(enemySpawnTimer, &QTimer::timeout, enemySpawnTimer, [this, scene, player]() {
        Enemy* enemy = EnemyFactory::create(HARD, scene, QPoint(615, 0), player);
        enemyObj.push_back(enemy);
        enemy->setZValue(500);
        scene->addItem(enemy);
    });

    enemySpawnTimer->start(TIME_RESET_MOB);
}

QTimer* ThirdLevel::getTimer()
{
    return enemySpawnTimer;
}

void ThirdLevel::deleteUi() {
    for (const auto& textureData : texturesObj) {
        if (textureData) delete textureData;
    }
    texturesObj.resize(0);

    for (const auto& enemyData : enemyObj) {
        if (enemyData) delete enemyData;
    }
    enemyObj.resize(0);
}
