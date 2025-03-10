#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include <QGraphicsItem>
#include "include/entities/view/entityview.h"

class EnemyView : public EntityView {
public:
    explicit EnemyView(const QPixmap& texture, QGraphicsItem* parent = nullptr)
        : EntityView(texture, parent) {}

    enum { Type = UserType + 10 };
    int type() const { return Type; }
};

#endif // ENEMYVIEW_H
