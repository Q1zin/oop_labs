#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Entity(QGraphicsScene* scene, int x, int y, int width, int height, const QString& img);
    Entity();

    ~Entity();

protected:
    void updateAllowedY();
    void updateAllowedX();
    void logicGo();
    void logicJump();
    void jump();
    void flip(const QString& position);

    QGraphicsScene* scene;
    int direction = 1; // 0 - left, 1 - right
    int x_speed = 0;
    float y_speed = 0;
    int y_jump_progress = 0;
    int state_jump = 0;
    int count_jump = 0;
    int allowed_go_left = 0;
    int allowed_go_right = 0;
    int allowed_go_up = 0;
    int allowed_go_down = 0;
};

#endif // ENTITY_H
