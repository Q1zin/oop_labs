#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

#include "include/entities/entity.h"

class Player : public Entity
{
    Q_OBJECT
public:
    Player(QGraphicsScene* scene, const QPoint& position, const QSize& size, const QString& img);

    ~Player();

    enum { Type = UserType + 1 };

    int type() const override;
    void advance(int phase) override;

    int getCoins();
    void setCoins(int count);

signals:
    void takenCoin();
    void takenShot();
    void heroDied();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    int countCoins = 0;
};

#endif // PLAYER_H
