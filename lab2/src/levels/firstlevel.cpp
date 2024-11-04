#include <QGraphicsScene>
#include "include/levels/firstlevel.h"
#include "include/entities/player.h"
#include "include/managers/texturefactory.h"

struct TextureData {
    QString type;
    QPoint position;
    QSize size;
};

void FirstLevel::loadLevel(QGraphicsScene *scene, Player* player) {
    std::vector<TextureData> textures = {
        {"regular", QPoint(160, scene->height() - 35), QSize(40, 35)},
        {"regular", QPoint(120, scene->height() - 50), QSize(40, 50)},
        {"regular", QPoint(200, scene->height() - 20), QSize(1080, 20)},
        {"regular", QPoint(220, 600), QSize(200, 20)},
        {"regular", QPoint(620, 600), QSize(200, 20)},
        {"regular", QPoint(420, 520), QSize(200, 20)},
        {"regular", QPoint(720, 450), QSize(200, 20)},
        {"regular", QPoint(420, 380), QSize(200, 20)},
        {"regular", QPoint(120, 310), QSize(200, 20)},
        {"regular", QPoint(670, 220), QSize(200, 20)},
        {"regular", QPoint(320, 220), QSize(200, 20)},
        {"regular", QPoint(0, 150), QSize(200, 20)},
        {"regular", QPoint(670, 120), QSize(200, 20)},
        {"regular", QPoint(900, 76), QSize(200, 20)},
        {"coin", QPoint(195, 250), QSize(0, 0)},
        {"coin", QPoint(750, 160), QSize(0, 0)},
        {"coin", QPoint(795, 390), QSize(0, 0)},
    };

    for (const auto& textureData : textures) {
        scene->addItem(TextureFactory::create(textureData.type, textureData.position, textureData.size));
    }
}
