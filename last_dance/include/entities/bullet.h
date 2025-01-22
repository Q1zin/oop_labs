#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsLineItem>
#include <QPointF>

class Bullet : public QObject, public QGraphicsLineItem {
    Q_OBJECT

public:
    Bullet(QPointF initPos, int direction);

signals:
    void collided(QGraphicsItem* item);

private:
    void advance(int phase);

    int x_speed;
};

#endif // BULLET_H
