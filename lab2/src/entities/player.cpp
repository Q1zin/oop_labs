#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPointF>

#include "include/entities/player.h"
#include "include/entities/bullet.h"
#include "include/textures/coinstexture.h"
#include "include/entities/enemy.h"
#include "gamecontroller.h"

#define PLAYER_MOVE_SPEED 4

Player::Player(QGraphicsScene* scene, const QPoint& position, const QSize& size, const QString& img)
    : Entity(scene, position, size, img) {
    controller = new GameController();
    connect(controller, &GameController::keyLeftPress, this, &Player::onKeyLeftPress);
    connect(controller, &GameController::keyRightPress, this, &Player::onKeyRightPress);
    connect(controller, &GameController::keyTopPress, this, &Player::onKeyTopPress);
    connect(controller, &GameController::keySpacePress, this, &Player::onKeySpacePress);
    connect(controller, &GameController::keyEscapePress, this, &Player::onKeyEscapePress);
    connect(controller, &GameController::keyLeftRelease, this, &Player::onKeyLeftRelease);
    connect(controller, &GameController::keyRightRelease, this, &Player::onKeyRightRelease);
}

Player::~Player() {
    for (auto& bulletData : bulletObj) {
        if (bulletData) {
            delete bulletData;
        }
    }
    bulletObj.resize(0);

    disconnect(controller, &GameController::keyLeftPress, this, &Player::onKeyLeftPress);
    disconnect(controller, &GameController::keyRightPress, this, &Player::onKeyRightPress);
    disconnect(controller, &GameController::keyTopPress, this, &Player::onKeyTopPress);
    disconnect(controller, &GameController::keySpacePress, this, &Player::onKeySpacePress);
    disconnect(controller, &GameController::keyEscapePress, this, &Player::onKeyEscapePress);
    disconnect(controller, &GameController::keyLeftRelease, this, &Player::onKeyLeftRelease);
    disconnect(controller, &GameController::keyRightRelease, this, &Player::onKeyRightRelease);
}

void Player::onKeyLeftPress() {
    setSpeed(QPointF(-PLAYER_MOVE_SPEED, getSpeed().y()));
    flip(Left);
}

void Player::onKeyRightPress() {
    setSpeed(QPointF(PLAYER_MOVE_SPEED, getSpeed().y()));
    flip(Right);
}

void Player::onKeyTopPress() {
    jump();
}

void Player::onKeySpacePress() {
    Bullet* bullet;
    if (getDirection() == 1) {
        bullet = new Bullet(mapToScene(QPointF(pixmap().width(), 32)), getDirection());
    } else {
        bullet = new Bullet(mapToScene(QPointF(0 - 10, 32)), getDirection());
    }
    connect(bullet, &Bullet::clearBullet, this, &Player::onClearBullet);
    scene->addItem(bullet);
    bulletObj.push_back(bullet);

    emit takenShot();
}

void Player::onKeyEscapePress() {
    emit pauseGame();
}

void Player::onKeyLeftRelease() {
    if (getSpeed().x() < 0) {
        setSpeed(QPointF(0, getSpeed().y()));
    }
}

void Player::onKeyRightRelease() {
    if (getSpeed().x() > 0) {
        setSpeed(QPointF(0, getSpeed().y()));
    }
}

void Player::onClearBullet(Bullet* bullet) {
    auto it = std::find(bulletObj.begin(), bulletObj.end(), bullet);
    if (it != bulletObj.end()) {
        bulletObj.erase(it);
        delete bullet;
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

void Player::keyPressEvent(QKeyEvent *event) {
    controller->keyPressEvent(event);
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    controller->keyReleaseEvent(event);
}

int Player::type() const
{
    return Type;
}
