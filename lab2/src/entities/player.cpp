#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPointF>

#include "include/entities/player.h"
#include "include/entities/bullet.h"
#include "include/textures/coinstexture.h"
#include "include/entities/enemy.h"

#define MAN_SPEED 4

Player::Player(QGraphicsScene* scene, int x, int y, int width, int height, const QString& img)
    : Entity(scene, x, y, width, height, img) {}

Player::~Player() {}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        x_speed = -MAN_SPEED;
        flip("left");
        break;
    case Qt::Key_Right:
        x_speed = MAN_SPEED;
        flip("right");
        break;
    case Qt::Key_Up:
        jump();
        break;
    case Qt::Key_Space:
        if (direction == 1) {
            scene->addItem(new Bullet(mapToScene(QPointF(pixmap().width() , 32)), direction, scene));
        } else {
            scene->addItem(new Bullet(mapToScene(QPointF(0 - 10, 32)), direction, scene)); // -10 размер пули
        }
        emit takeShot();
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        x_speed = 0;
    } else if (event->key() == Qt::Key_Right) {
        x_speed = 0;
    }
}


void Player::advance(int phase)
{
    if (phase) {
        updateAllowedY();
        updateAllowedX();
        logicGo();
        logicJump();
    } else {
        foreach (QGraphicsItem* item, collidingItems()) {
            if (item->type() == CoinsTexture::Type) {
                delete item;
                countCoins++;
                emit takeCoin();
            } else if (item->type() == Enemy::Type) {
                emit heroDied();
            }
        }
    }
}

int Player::getCoins()
{
    return countCoins;
}

void Player::setCoins(int count)
{
    countCoins = count;
}

int Player::type() const
{
    return Type;
}
