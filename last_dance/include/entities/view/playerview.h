#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

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

class PlayerView : public EntityView {
public:
    explicit PlayerView(const QPixmap& texture, QGraphicsItem* parent = nullptr);

    QList<QGraphicsItem*> getCollision();
};

#endif // PLAYERVIEW_H
