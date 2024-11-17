#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QTimer>
#include "include/entities/player.h"
#include "include/managers/texturefactory.h"

class Level {
protected:
    int bestTime;
public:
    Level();
    virtual ~Level() = default;

    virtual void loadLevel(QGraphicsScene* scene, TextureFactory<ITexture, QString> textureFactory, Player* player = nullptr) = 0;
    virtual QTimer* getTimer();
    virtual void deleteUi();
    int getBestTime() const;
    void setBestTime(int time);
};

#endif // LEVEL_H
