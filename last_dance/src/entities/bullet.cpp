#include <QGraphicsScene>
#include <QPen>

#include "include/entities/bullet.h"
#include "include/entities/view/enemyview.h"
#include "include/textures/texture.h"

#define BULLET_LENGTH 10
#define BULLET_SPEED 10

Bullet::Bullet(QPointF initPos, int direction)
    : QGraphicsLineItem(0){
    if (direction == -1) {
        x_speed = -BULLET_SPEED;
    } else {
        x_speed = BULLET_SPEED;
    }

    setPen(QPen(QBrush(Qt::red), 3));
    setLine(0, 0, BULLET_LENGTH, 0);
    setPos(initPos);
}


void Bullet::advance(int phase) {
    if (phase) {
        moveBy(x_speed, 0);

        QPointF bulletPos = scenePos();
        if (data(0).toBool() || bulletPos.x() < 0 || bulletPos.x() > 1280 - BULLET_LENGTH){
            delete this;
            return;
        }
    } else {
        foreach (QGraphicsItem* item, collidingItems()) {
            if (item->type() == Texture::Type || item->type() == EnemyView::Type) {
                emit collided(item);
                setData(0, true);
            }
        }
    }
}
