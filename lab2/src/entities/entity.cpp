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

    allowedMovement.left = dist_left - 2;
    allowedMovement.right = dist_right - 2;
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

    allowedMovement.up = dist_up - 2;
    allowedMovement.down = dist_down - 2;
}

void Entity::move()
{
    if (speed.x() > 0) {
        if (allowedMovement.right > speed.x()) {
            moveBy(speed.x(), 0);
        } else if (allowedMovement.right != 0) {
            moveBy(allowedMovement.right, 0);
        }
    } else if (speed.x() < 0) {
        if (allowedMovement.left > std::abs(speed.x())) {
            moveBy(speed.x(), 0);
        } else if (allowedMovement.left != 0) {
            moveBy(-allowedMovement.left, 0);
        }
    }
}

void Entity::jump()
{
    if ((count_jump == 0 && allowedMovement.down != 0) || (count_jump == 1)) {
        state_jump = 2;
        y_jump_progress = 0;
    } else if (count_jump == 0) {
        state_jump = 1;
        y_jump_progress = 0;
    }
}

void Entity::logicJump() {
    if (state_jump != 1 && state_jump != 2) {
        speed.setY(speed.y() + GRAVITY);

        if (allowedMovement.down >= speed.y()) {
            moveBy(0, speed.y());
        } else {
            moveBy(0, allowedMovement.down);
            state_jump = 0;
            count_jump = 0;
            speed.setY(0);
        }
    } else if (state_jump == 1) {
        count_jump = 1;

        if (y_jump_progress < MAX_JUMP_HEIGHT) {
            y_jump_progress += JUMP_FORCE;
            if (allowedMovement.up >= JUMP_FORCE) {
                moveBy(0, -JUMP_FORCE);
            } else {
                state_jump = 0;
            }
        } else {
            state_jump = 0;
        }
    } else if (state_jump == 2) {
        count_jump = 2;

        if (y_jump_progress < MAX_JUMP_HEIGHT) {
            y_jump_progress += JUMP_FORCE;
            if (allowedMovement.up >= JUMP_FORCE) {
                moveBy(0, -JUMP_FORCE);
            } else {
                state_jump = 0;
            }
        } else {
            state_jump = 0;
        }
    }
}

void Entity::flip(Direction position)
{
    if (position == Right && direction == 0) {
        QTransform transform;
        transform.scale(-1, 1);
        setPixmap(pixmap().transformed(transform));
        direction = 1;
    } else if (position == Left && direction == 1) {
        QTransform transform;
        transform.scale(-1, 1);
        setPixmap(pixmap().transformed(transform));
        direction = 0;
    }
}
