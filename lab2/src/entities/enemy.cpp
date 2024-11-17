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

Enemy::~Enemy() {
    if (HuntTimer) {
        HuntTimer->stop();
        delete HuntTimer;
    }
}

void Enemy::advance(int phase) {
    if (phase) {
        allowed_go_left_old = getAllowedMovement().left;
        allowed_go_right_old = getAllowedMovement().right;
        updataAllowedMovement();
        move();
        logicJump();
        logicHunt();
    } else {
        if (data(0).toBool()){
            setData(0, false);
            setHp(getHp() - 1);
            if (getHp() <= 0) {
                this->hide();
                return;
            }
        }
    }
}

void Enemy::checkBlock(){
    qreal playerX = victim->x();
    if (std::abs(playerX - x()) < 5) {
        setSpeed(QPointF(0, getSpeed().y()));
        return;
    }

    if (allowed_go_left_old == getAllowedMovement().left || allowed_go_right_old == getAllowedMovement().right) {
        jump();
    }
}

int Enemy::type() const
{
    return Type;
}

int Enemy::getHp(){ return hp; }

void Enemy::setHp(int hp_) { hp = hp_; }


void Enemy::logicHunt() {
    qreal playerX = victim->x();

    if (std::abs(playerX - x()) < 5) {
        setSpeed(QPointF(0, getSpeed().y()));
        return;
    }

    if (x() < playerX) {
        setSpeed(QPointF(ENEMY_SPEED, getSpeed().y()));
        flip(Left);
    } else if (x() > playerX) {
        setSpeed(QPointF(-ENEMY_SPEED, getSpeed().y()));
        flip(Right);
    }
}
