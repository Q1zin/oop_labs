#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QTimer>
#include "include/entities/player.h"

class Level {
protected:
    int bestTime;
public:
    Level();

    virtual void loadLevel(QGraphicsScene* scene, Player* player = nullptr) = 0;
    virtual QTimer* getTimer();
    int getBestTime() const;
    void setBestTime(int time);
};

#endif // LEVEL_H
