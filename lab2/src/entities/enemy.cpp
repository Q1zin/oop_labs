#include <QTimer>

#include "include/entities/enemy.h"
#include "include/entities/player.h"

#define ENEMY_SPEED 2

Enemy::Enemy(QGraphicsScene* scene, const QPoint& position, const QSize& size, int hp, const QString& img, Player* victim)
    : Entity(scene, position, size, img), victim(victim), hp(hp) {
    HuntTimer = new QTimer(this);
    connect(HuntTimer, &QTimer::timeout, this, &Enemy::checkBlock);
    HuntTimer->start(100);
}

Enemy::Enemy() : Entity(), victim(nullptr), hp(0) {
    HuntTimer = nullptr;
}

Enemy::~Enemy()
{
    if (HuntTimer) {
        HuntTimer->stop();
        delete HuntTimer;
    }
}

void Enemy::advance(int phase) {
    if (phase) {
        allowed_go_left_old = allowedMovement.left;
        allowed_go_right_old = allowedMovement.right;
        updataAllowedMovement();
        move();
        logicJump();
        logicHunt();
    } else {
        if (data(0).toBool()){
            setData(0, false);
            hp -= 1;
            if (hp <= 0) {
                delete this;
                return;
            }
        }
    }
}

void Enemy::checkBlock(){
    qreal playerX = victim->x();
    if (std::abs(playerX - x()) < 5) {
        speed.setX(0);
        return;
    }

    if (allowed_go_left_old == allowedMovement.left || allowed_go_right_old == allowedMovement.right) {
        jump();
    }
}

int Enemy::type() const
{
    return Type;
}

void Enemy::logicHunt() {
    qreal playerX = victim->x();

    if (std::abs(playerX - x()) < 5) {
        speed.setX(0);
        return;
    }

    if (x() < playerX) {
        speed.setX(ENEMY_SPEED);
        flip(Left);
    } else if (x() > playerX) {
        speed.setX(-ENEMY_SPEED);
        flip(Right);
    }
}
