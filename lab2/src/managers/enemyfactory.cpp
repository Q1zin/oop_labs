#include "include/managers/enemyfactory.h"

EnemyFactory::EnemyFactory() {}

Enemy *EnemyFactory::create(EnemyType type, QGraphicsScene *scene, const QPoint &position, Player *victim) {
    switch (type) {
    case EASY:
        return new Enemy(scene, position, QSize(50, 50), 1, ":/img/enemy_type_1.png", victim);
    case MEDIUM:
        return new Enemy(scene, position, QSize(50, 50), 10, ":/img/enemy_type_2.png", victim);
    case HARD:
        return new Enemy(scene, position, QSize(50, 50), 20, ":/img/enemy_type_3.png", victim);
    }
}
