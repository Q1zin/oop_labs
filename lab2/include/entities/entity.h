#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPointF>

enum Direction {
    Left,
    Right
};

struct MovementAllowance {
    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;
};

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Entity(QGraphicsScene* scene, const QPoint& position, const QSize& size, const QString& img);
    Entity();

    ~Entity();

protected:
    void updataAllowedMovement();
    void move();
    void logicJump();
    void jump();
    void flip(Direction position);

    QGraphicsScene* scene;
    int direction = 1; // 0 - left, 1 - right
    QPointF speed = {0 ,0};
    int y_jump_progress = 0;
    int state_jump = 0;
    int count_jump = 0;
    MovementAllowance allowedMovement = {0, 0, 0, 0};

private:
    void updateAllowedY();
    void updateAllowedX();
};


#endif // ENTITY_H
