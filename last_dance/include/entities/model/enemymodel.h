#ifndef ENEMYMODEL_H
#define ENEMYMODEL_H

#include "include/entities/model/entitymodel.h"

class EnemyModel : public EntityModel {
    Q_OBJECT

public:
    explicit EnemyModel(QPointF position, QObject* parent = nullptr)
        : EntityModel(position, parent) {}
};

#endif // ENEMYMODEL_H
