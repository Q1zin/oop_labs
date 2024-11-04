#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPointF>

#include "include/entities/player.h"
#include "include/entities/bullet.h"
#include "include/textures/coinstexture.h"
#include "include/entities/enemy.h"

#define PLAYER_MOVE_SPEED 4

Player::Player(QGraphicsScene* scene, const QPoint& position, const QSize& size, const QString& img)
    : Entity(scene, position, size, img) {}

Player::~Player() {}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        speed.setX(-PLAYER_MOVE_SPEED);
        flip(Left);
        break;
    case Qt::Key_Right:
        speed.setX(PLAYER_MOVE_SPEED);
        flip(Right);
        break;
    case Qt::Key_Up:
        jump();
        break;
    case Qt::Key_Space:
        if (direction == 1) {
            scene->addItem(new Bullet(mapToScene(QPointF(pixmap().width() , 32)), direction));
        } else {
            scene->addItem(new Bullet(mapToScene(QPointF(0 - 10, 32)), direction)); // -10 размер пули
        }
        emit takenShot();
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        speed.setX(0);
    } else if (event->key() == Qt::Key_Right) {
        speed.setX(0);
    }
}


void Player::advance(int phase)
{
    if (phase) {
        updataAllowedMovement();
        move();
        logicJump();
    } else {
        foreach (QGraphicsItem* item, collidingItems()) {
            if (item->type() == CoinsTexture::Type) {
                delete item;
                countCoins++;
                emit takenCoin();
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
