#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QTransform>

#include "include/entities/entity.h"
#include "include/textures/texture.h"

#define MAX_JUMP_HEIGHT 80
#define INIT_MAX_DIST 999999999
#define GRAVITY 0.2
#define JUMP_FORCE 5

Entity::Entity(QGraphicsScene* scene, const QPoint& position, const QSize& size, const QString& img)
    : QObject(0), QGraphicsPixmapItem(0), scene(scene) {
    setPixmap(img);
    setPixmap(pixmap().scaled(size.width(), size.height(), Qt::KeepAspectRatio));
    setPos(position.x(), position.y());
}

Entity::Entity() : QObject(0), QGraphicsPixmapItem(0) {}

Entity::~Entity() {}

int Entity::getDirection() const { return direction; }

QPointF Entity::getSpeed() const { return speed; }

int Entity::getYJumpProgress() const { return y_jump_progress; }

int Entity::getStateJump() const { return state_jump; }

int Entity::getCountJump() const { return count_jump; }

MovementAllowance Entity::getAllowedMovement() const { return allowedMovement; }

void Entity::setDirection(int direction_) { direction = direction_; }

void Entity::setSpeed(const QPointF &speed_) { speed = speed_; }

void Entity::setYJumpProgress(int progress) { y_jump_progress = progress; }

void Entity::setStateJump(int state) { state_jump = state; }

void Entity::setCountJump(int count) { count_jump = count; }

void Entity::setAllowedMovement(const MovementAllowance &movement) { allowedMovement = movement; }

void Entity::updataAllowedMovement()
{
    updateAllowedX();
    updateAllowedY();
}

void Entity::updateAllowedX() {
    int dist_left = INIT_MAX_DIST;
    int dist_right = INIT_MAX_DIST;

    int center_man = x() + (pixmap().width() / 2);

    for (QGraphicsItem* item : scene->items()) {
        if (item->type() == Texture::Type) {
            QRectF boundingRect = item->boundingRect();
            QPointF position = item->pos();

            int item_x = position.x();
            int item_y = position.y();
            int item_height = boundingRect.height();

            if (item_y + item_height >= y() && item_y <= y() + pixmap().height()) {
                int gap = item_x - center_man;

                if (gap > 0) {
                    gap -= pixmap().width() / 2;
                    dist_right = std::min(dist_right, std::abs(gap));
                } else {
                    gap += boundingRect.width() + pixmap().width() / 2;
                    dist_left = std::min(dist_left, std::abs(gap));
                }
            }
        }
    }

    if (dist_left == INIT_MAX_DIST) {
        dist_left = x();
    }

    if (dist_right == INIT_MAX_DIST) {
        dist_right = scene->width() - x() - pixmap().width();
    }

    setAllowedMovement({dist_left - 2, dist_right - 2, getAllowedMovement().up, getAllowedMovement().down});
}

void Entity::updateAllowedY() {
    int dist_up = INIT_MAX_DIST;
    int dist_down = INIT_MAX_DIST;

    int center_man = y() + (pixmap().height() / 2);

    for (QGraphicsItem* item : scene->items()) {
        if (item->type() == Texture::Type) {
            QRectF boundingRect = item->boundingRect();
            QPointF position = item->pos();

            int item_x = position.x();
            int item_y = position.y();
            int item_width = boundingRect.width();

            if (item_x + item_width >= x() && item_x <= x() + pixmap().width()) {
                int gap = item_y - center_man;

                if (gap > 0) {
                    gap -= pixmap().height() / 2;
                    dist_down = std::min(dist_down, std::abs(gap));
                } else {
                    gap += boundingRect.height() + pixmap().height() / 2;
                    dist_up = std::min(dist_up, std::abs(gap));
                }
            }
        }
    }

    if (dist_up == INIT_MAX_DIST) {
        dist_up = y();
    }

    if (dist_down == INIT_MAX_DIST) {
        dist_down = scene->height() - y() - pixmap().height();
    }

    setAllowedMovement({getAllowedMovement().left, getAllowedMovement().right, dist_up - 2, dist_down - 2});
}

void Entity::move() {
    if (getSpeed().x() > 0) {
        if (getAllowedMovement().right > getSpeed().x()) {
            moveBy(getSpeed().x(), 0);
        } else if (getAllowedMovement().right != 0) {
            moveBy(getAllowedMovement().right, 0);
        }
    } else if (getSpeed().x() < 0) {
        if (getAllowedMovement().left > std::abs(getSpeed().x())) {
            moveBy(getSpeed().x(), 0);
        } else if (getAllowedMovement().left != 0) {
            moveBy(-getAllowedMovement().left, 0);
        }
    }
}

void Entity::jump() {
    if ((getCountJump() == 0 && getAllowedMovement().down != 0) || (getCountJump() == 1)) {
        setStateJump(2);
        setYJumpProgress(0);
    } else if (getCountJump() == 0) {
        setStateJump(1);
        setYJumpProgress(0);
    }
}

void Entity::logicJump() {
    if (getStateJump() != 1 && getStateJump() != 2) {
        setSpeed(QPointF(getSpeed().x(), getSpeed().y() + GRAVITY));
        if (getAllowedMovement().down >= getSpeed().y()) {
            moveBy(0, getSpeed().y());
        } else {
            moveBy(0, getAllowedMovement().down);
            setStateJump(0);
            setCountJump(0);
            setSpeed(QPointF(getSpeed().x(), 0));
        }
    } else if (getStateJump() == 1) {
        setCountJump(1);
        if (getYJumpProgress() < MAX_JUMP_HEIGHT) {
            setYJumpProgress(getYJumpProgress() + JUMP_FORCE);
            if (getAllowedMovement().up >= JUMP_FORCE) {
                moveBy(0, -JUMP_FORCE);
            } else {
                setStateJump(0);
            }
        } else {
            setStateJump(0);
        }
    } else if (getStateJump() == 2) {
        setCountJump(2);
        if (getYJumpProgress() < MAX_JUMP_HEIGHT) {
            setYJumpProgress(getYJumpProgress() + JUMP_FORCE);
            if (getAllowedMovement().up >= JUMP_FORCE) {
                moveBy(0, -JUMP_FORCE);
            } else {
                setStateJump(0);
            }
        } else {
            setStateJump(0);
        }
    }
}

void Entity::flip(Direction position) {
    if (position == Right && getDirection() == 0) {
        QTransform transform;
        transform.scale(-1, 1);
        setPixmap(pixmap().transformed(transform));
        setDirection(1);
    } else if (position == Left && getDirection() == 1) {
        QTransform transform;
        transform.scale(-1, 1);
        setPixmap(pixmap().transformed(transform));
        setDirection(0);
    }
}
