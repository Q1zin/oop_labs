#include <QPen>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "include/entities/view/entityview.h"
#include "include/entities/controller/playercontroller.h"
#include "include/textures/coinstexture.h"
#include "include/textures/invisibletexture.h"
#include "include/entities/view/enemyview.h"
#include "include/entities/view/playerview.h"

PlayerView::PlayerView(const QPixmap &texture, QGraphicsItem *parent)
    : EntityView(texture, parent) {}

QList<QGraphicsItem *> PlayerView::getCollision() {
    QList<QGraphicsItem*> collidingItems;

    for (QGraphicsItem* other : this->scene()->items()) {
        if (other != this && (other->type() == CoinsTexture::Type || other->type() == InvisibleTexture::Type || other->type() == EnemyView::Type)) {
            if (this->collidesWithItem(other)) {
                collidingItems.append(other);
            }
        }
    }

    return collidingItems;
}
