#include <QGraphicsScene>
#include <QPen>

#include "include/entities/bullet.h"
#include "include/entities/enemy.h"
#include "include/textures/texture.h"

#define BULLET_LENGTH 10
#define BULLET_SPEED 5

Bullet::Bullet(QPointF initPos, int direction)
    : QGraphicsLineItem(0) {
    if (direction == 0) {
        x_speed = -BULLET_SPEED;
    } else {
        x_speed = BULLET_SPEED;
    }

    setPen(QPen(QBrush(Qt::red), 3));
    setLine(0, 0, BULLET_LENGTH, 0);
    setPos(initPos);
}

Bullet::~Bullet() {}


void Bullet::advance(int phase) {
    if (phase) {
        moveBy(x_speed, 0);
        if (data(0).toBool()){
            emit clearBullet(this);
        }
    } else {
        foreach (QGraphicsItem* item, collidingItems()) {
            if ((item->type() == Texture::Type) || (item->type() == Enemy::Type)) {
                item->setData(0, true);
                setData(0, true);
            }
        }

        if (x() < 0 || x() + BULLET_LENGTH > scene()->width()){
            emit clearBullet(this);
        }
    }
}
