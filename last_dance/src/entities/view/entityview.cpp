#include "include/entities/view/entityview.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPen>
#include <QGraphicsScene>
#include <QTimer>

EntityView::EntityView(const QPixmap &texture, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent) {
    setPixmap(texture);
}

void EntityView::updatePosition(const QPointF &position) {
    setPos(position);
}

QList<QGraphicsItem *> EntityView::getPredictCollision(QPointF velocity) {
    QRectF futureBoundingBox = this->sceneBoundingRect().translated(velocity);

    QList<QGraphicsItem*> collidingItems;
    for (QGraphicsItem* other : this->scene()->items(futureBoundingBox)) {
        if (other != this && other->type() == Texture::Type) {
            if (other->sceneBoundingRect().intersects(futureBoundingBox)) {
                collidingItems.append(other);
            }
        }
    }

    return collidingItems;
}
