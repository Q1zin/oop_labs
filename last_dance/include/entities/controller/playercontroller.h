#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QPointF>
#include "include/entities/controller/entitycontroller.h"
#include "include/entities/model/playermodel.h"

class PlayerView;

class PlayerController : public EntityController {
    Q_OBJECT

public:
    explicit PlayerController(PlayerModel* model, PlayerView* view, QObject* parent = nullptr);

    ~PlayerController() = default;

    void handleKeyPress(QKeyEvent* event);
    void handleKeyRelease(QKeyEvent* event);

    void update() override;

signals:
    void playerTakeCoin(QGraphicsItem* coin);
    void playerFinished();
    void playerDie();
    void playerShoot();

private:
    void flip(int position);

    PlayerModel* model;
    PlayerView* view;
    int remainingJumps;
    const int maxJumps = 2;
    bool wasOnGround;
};

#endif // PLAYERCONTROLLER_H
