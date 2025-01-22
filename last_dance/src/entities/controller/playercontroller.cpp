#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QTransform>
#include "include/entities/controller/playercontroller.h"
#include "include/entities/view/playerview.h"
#include "include/textures/coinstexture.h"
#include "include/textures/invisibletexture.h"
#include "include/entities/view/enemyview.h"


PlayerController::PlayerController(PlayerModel* model, PlayerView* view, QObject* parent)
    : EntityController(model, view, parent), model(model), view(view), maxJumps(2) {
    remainingJumps = model->getIsOnGround() ? maxJumps : 1;
    wasOnGround = model->getIsOnGround();
}

void PlayerController::handleKeyPress(QKeyEvent* event) {
    if (!model) return;
    switch (event->key()) {
    case Qt::Key_A:
        model->setVelocity(QPointF(-5, model->getVelocity().y()));
        flip(-1);
        break;
    case Qt::Key_D:
        model->setVelocity(QPointF(5, model->getVelocity().y()));
        flip(1);
        break;
    case Qt::Key_W:
        if (remainingJumps > 0) {
            model->setVelocity(QPointF(model->getVelocity().x(), -18));
            remainingJumps--;
        }
        break;
    case Qt::Key_Space:
        emit playerShoot();
        break;
    }
}

void PlayerController::handleKeyRelease(QKeyEvent* event) {
    if (!model) return;

    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_D:
        model->setVelocity(QPointF(0, model->getVelocity().y()));
        break;
    }
}

void PlayerController::update() {
    EntityController::update();

    bool isOnGround = model->getIsOnGround();

    if (wasOnGround && !isOnGround && remainingJumps == maxJumps) {
        remainingJumps = 1;
    }

    if (isOnGround) {
        remainingJumps = maxJumps;
    }

    wasOnGround = isOnGround;

    QList<QGraphicsItem*> collidingItems = view->getCollision();
    for (QGraphicsItem* item : collidingItems) {
        if (item->type() == CoinsTexture::Type) {
            emit playerTakeCoin(item);
        } else if (item->type() == InvisibleTexture::Type) {
            emit playerFinished();
        } else if (item->type() == EnemyView::Type) {
            emit playerDie();
        }
    }
}

void PlayerController::flip(int position) {
    if (position == 1 && model->getDirection() == -1) { // 1 - вправо, -1 - влево
        QTransform transform;
        transform.scale(-1, 1);
        view->setPixmap(view->pixmap().transformed(transform));
        model->setDirection(1);
    } else if (position == -1 && model->getDirection() == 1) {
        QTransform transform;
        transform.scale(-1, 1);
        view->setPixmap(view->pixmap().transformed(transform));
        model->setDirection(-1);
    }
}
