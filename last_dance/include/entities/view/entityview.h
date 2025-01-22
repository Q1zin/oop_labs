#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPen>
#include <QGraphicsScene>
#include <QTimer>
#include "include/textures/texture.h"

class EntityView : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit EntityView(const QPixmap& texture, QGraphicsItem* parent = nullptr);
    ~EntityView() = default;

    void updatePosition(const QPointF& position);

    QList<QGraphicsItem*> getPredictCollision(QPointF velocity);
};

#endif // ENTITYVIEW_H
