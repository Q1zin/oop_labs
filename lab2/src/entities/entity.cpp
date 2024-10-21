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

Entity::Entity(QGraphicsScene* scene, int x, int y, int width, int height, const QString& img)
    : QObject(0), QGraphicsPixmapItem(0), scene(scene) {
    setPixmap(img);
    setPixmap(pixmap().scaled(width, height, Qt::KeepAspectRatio));
    setPos(x, y);
}

Entity::Entity() : QObject(0), QGraphicsPixmapItem(0) {}

Entity::~Entity() {}

void Entity::updateAllowedX() {
    int dist_left = INIT_MAX_DIST;
    int dist_right = INIT_MAX_DIST;

    int center_man = this->x() + (this->pixmap().width() / 2);

    for (QGraphicsItem* item : scene->items()) {
        if (item->type() == Texture::Type) {
            QRectF boundingRect = item->boundingRect();
            QPointF position = item->pos();

            int item_x = position.x();
            int item_y = position.y();
            int item_height = boundingRect.height();

            if (item_y + item_height >= this->y() && item_y <= this->y() + this->pixmap().height()) {
                int gap = item_x - center_man;

                if (gap > 0) {
                    gap -= this->pixmap().width() / 2;
                    dist_right = std::min(dist_right, std::abs(gap));
                } else {
                    gap += boundingRect.width() + this->pixmap().width() / 2;
                    dist_left = std::min(dist_left, std::abs(gap));
                }
            }
        }
    }

    if (dist_left == INIT_MAX_DIST) {
        dist_left = this->x();
    }

    if (dist_right == INIT_MAX_DIST) {
        dist_right = scene->width() - this->x() - this->pixmap().width();
    }

    allowed_go_left = dist_left - 2;
    allowed_go_right = dist_right - 2;
}

void Entity::updateAllowedY() {
    int dist_up = INIT_MAX_DIST;
    int dist_down = INIT_MAX_DIST;

    int center_man = this->y() + (this->pixmap().height() / 2);

    for (QGraphicsItem* item : scene->items()) {
        if (item->type() == Texture::Type) {
            QRectF boundingRect = item->boundingRect();
            QPointF position = item->pos();

            int item_x = position.x();
            int item_y = position.y();
            int item_width = boundingRect.width();

            if (item_x + item_width >= this->x() && item_x <= this->x() + this->pixmap().width()) {
                int gap = item_y - center_man;

                if (gap > 0) {
                    gap -= this->pixmap().height() / 2;
                    dist_down = std::min(dist_down, std::abs(gap));
                } else {
                    gap += boundingRect.height() + this->pixmap().height() / 2;
                    dist_up = std::min(dist_up, std::abs(gap));
                }
            }
        }
    }

    if (dist_up == INIT_MAX_DIST) {
        dist_up = this->y();
    }

    if (dist_down == INIT_MAX_DIST) {
        dist_down = scene->height() - this->y() - this->pixmap().height();
    }

    allowed_go_up = dist_up - 2;
    allowed_go_down = dist_down - 2;
}

void Entity::logicGo()
{
    if (x_speed > 0) {
        if (allowed_go_right > x_speed) {
            moveBy(x_speed, 0);
        } else if (allowed_go_right != 0) {
            moveBy(allowed_go_right, 0);
        }
    } else if (x_speed < 0) {
        if (allowed_go_left > std::abs(x_speed)) {
            moveBy(x_speed, 0);
        } else if (allowed_go_left != 0) {
            moveBy(-allowed_go_left, 0);
        }
    }
}

void Entity::jump()
{
    if ((count_jump == 0 && allowed_go_down != 0) || (count_jump == 1)) {
        state_jump = 2;
        y_jump_progress = 0;
    } else if (count_jump == 0) {
        state_jump = 1;
        y_jump_progress = 0;
    }
}

void Entity::logicJump() {
    if (state_jump != 1 && state_jump != 2) {
        y_speed += GRAVITY;

        if (allowed_go_down >= y_speed) {
            moveBy(0, y_speed);
        } else {
            moveBy(0, allowed_go_down);
            state_jump = 0;
            count_jump = 0;
            y_speed = 0;
        }
    } else if (state_jump == 1) {
        count_jump = 1;

        if (y_jump_progress < MAX_JUMP_HEIGHT) {
            y_jump_progress += JUMP_FORCE;
            if (allowed_go_up >= JUMP_FORCE) {
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
            if (allowed_go_up >= JUMP_FORCE) {
                moveBy(0, -JUMP_FORCE);
            } else {
                state_jump = 0;
            }
        } else {
            state_jump = 0;
        }
    }
}

void Entity::flip(const QString& position)
{
    if (position == "right" && direction == 0) {
        QTransform transform;
        transform.scale(-1, 1);
        this->setPixmap(pixmap().transformed(transform));
        direction = 1;
    } else if (position == "left" && direction == 1) {
        QTransform transform;
        transform.scale(-1, 1);
        this->setPixmap(pixmap().transformed(transform));
        direction = 0;
    }
}
