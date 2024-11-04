#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsLineItem>
#include <QPointF>

class Bullet : public QGraphicsLineItem {
public:
    Bullet(QPointF initPos, int direction);

private:
    void advance(int phase);

    int x_speed;
};

#endif // BULLET_H
