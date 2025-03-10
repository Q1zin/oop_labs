#include "include/entities/model/entitymodel.h"
#include <QPointF>
#include "include/textures/texture.h"

EntityModel::EntityModel(QPointF position, QObject *parent)
    : QObject(parent), position(position), velocity(0, 0), health(100), isOnGround(false), gravity(1) {}

QPointF EntityModel::getPosition() const { return position; }

void EntityModel::setPosition(const QPointF &pos) { position = pos; }

QPointF EntityModel::getVelocity() const { return velocity; }

void EntityModel::setVelocity(const QPointF &vel) { velocity = vel; }

bool EntityModel::getIsOnGround() { return isOnGround; }

void EntityModel::setHealth(int _health) { health = _health; }

void EntityModel::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
    emit healthChanged(health);
}

bool EntityModel::isAlive() const { return health > 0; }

void EntityModel::move(QList<QGraphicsItem *> collidedItems) {
    QPointF positionRect = position + velocity;
    int playerLeft = positionRect.x();
    int playerRight = positionRect.x() + 50;
    int playerTop = positionRect.y();
    int playerBottom = positionRect.y() + 50;

    if (playerLeft <= 0) position.setX(0);
    if (playerRight >= 1280) position.setX(1280 - 50);
    if (playerTop <= 0) { position.setY(0); velocity.setY(0);}
    if (playerBottom >= 720) position.setY(720 - 50);

    isOnGround = false;

    for (QGraphicsItem* texture : collidedItems) {
        int textureX = texture->x();
        int textureY = texture->y();
        int textureWidth = texture->boundingRect().width();
        int textureHeight = texture->boundingRect().height();

        int overlapX = std::min(playerRight, textureX + textureWidth) - std::max(playerLeft, textureX);
        int overlapY = std::min(playerBottom, textureY + textureHeight) - std::max(playerTop, textureY);

        if (overlapX > 0 && overlapY > 0) {
            if (overlapY < overlapX) {
                if (velocity.y() >= 0 && playerBottom > textureY) {
                    velocity.setY(0);
                    position.setY(textureY - 50);
                    isOnGround = true;
                } else if (velocity.y() < 0 && playerTop < textureY + textureHeight) {
                    velocity.setY(gravity);
                    position.setY(textureY + textureHeight);
                }
            } else {
                if (velocity.x() > 0 && playerRight > textureX) {
                    velocity.setX(0);
                    position.setX(textureX - 50);
                } else if (velocity.x() < 0 && playerLeft < textureX + textureWidth) {
                    velocity.setX(0);
                    position.setX(textureX + textureWidth);
                }
            }
        }
    }

    position += velocity;
    velocity.setY(velocity.y() + gravity);
    emit positionChanged(position);
}




