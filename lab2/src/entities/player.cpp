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

Player::~Player() {
    for (auto& bulletData : bulletObj) {
        if (bulletData) {
            delete bulletData;
        }
    }
    bulletObj.resize(0);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        setSpeed(QPointF(-PLAYER_MOVE_SPEED, getSpeed().y()));
        flip(Left);
        break;
    case Qt::Key_Right:
        setSpeed(QPointF(PLAYER_MOVE_SPEED, getSpeed().y()));
        flip(Right);
        break;
    case Qt::Key_Up:
        jump();
        break;
    case Qt::Key_Space:
        Bullet* bullet;
        if (getDirection() == 1) {
            bullet = new Bullet(mapToScene(QPointF(pixmap().width() , 32)), getDirection());
        } else {
            bullet = new Bullet(mapToScene(QPointF(0 - 10, 32)), getDirection());
        }
        connect(bullet, &Bullet::clearBullet, this, &Player::onClearBullet);
        scene->addItem(bullet);
        bulletObj.push_back(bullet);

        emit takenShot();
        break;
    }
}

void Player::onClearBullet(Bullet* bullet) {
    auto it = std::find(bulletObj.begin(), bulletObj.end(), bullet);
    if (it != bulletObj.end()) {
        bulletObj.erase(it);
        delete bullet;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        setSpeed(QPointF(0, getSpeed().y()));
    }
}


void Player::advance(int phase) {
    if (phase) {
        updataAllowedMovement();
        move();
        logicJump();
    } else {
        foreach (QGraphicsItem* item, collidingItems()) {
            if (item->type() == CoinsTexture::Type) {
                item->hide();
                setCoins(getCoins() + 1);
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
