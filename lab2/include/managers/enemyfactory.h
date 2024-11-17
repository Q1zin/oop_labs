#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "include/entities/enemy.h"

enum EnemyType { EASY, MEDIUM, HARD };

class EnemyFactory
{
public:
    EnemyFactory();

    static Enemy* create(EnemyType type, QGraphicsScene* scene, const QPoint& position, Player* victim);
};

#endif // ENEMYFACTORY_H
