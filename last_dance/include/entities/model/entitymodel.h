#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include <QObject>
#include <QPointF>
#include "include/textures/texture.h"

class EntityModel : public QObject {
    Q_OBJECT

protected:
    QPointF position;
    QPointF velocity;
    int health;
    bool isOnGround;
    double gravity;

public:
    explicit EntityModel(QPointF position, QObject* parent = nullptr);

    QPointF getPosition() const;
    void setPosition(const QPointF& pos);

    QPointF getVelocity() const;
    void setVelocity(const QPointF& vel);

    bool getIsOnGround();

    void move(QList<QGraphicsItem*> collidedItems = {});

    void setHealth(int health);

    virtual void takeDamage(int amount);
    virtual bool isAlive() const;

signals:
    void positionChanged(const QPointF& newPosition);
    void healthChanged(int newHealth);
};

#endif // ENTITYMODEL_H
