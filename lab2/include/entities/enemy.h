#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsScene>
#include <QTimer>

#include "include/entities/entity.h"
#include "include/entities/player.h"

class Enemy : public Entity
{
    Q_OBJECT
public:
    Enemy(QGraphicsScene* scene, int x, int y, int width, int height, int hp, const QString& img, Player* victim);
    Enemy();

    ~Enemy();

    int type() const override;

    enum { Type = UserType + 2 };

public slots:
    void checkBlock();

private:
    void advance(int phase) override;
    void logicHunt();

    QTimer* HuntTimer;
    Player* victim;

    int hp;
    int allowed_go_left_old;
    int allowed_go_right_old;
};

#endif // ENEMY_H

