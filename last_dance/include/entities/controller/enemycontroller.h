#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include <QPointF>
#include "include/entities/controller/entitycontroller.h"
#include "include/entities/model/enemymodel.h"
#include "include/entities/view/enemyview.h"

class EnemyController : public EntityController {
    Q_OBJECT

public:
    explicit EnemyController(EnemyModel* model, EnemyView* view, QObject* parent = nullptr);
    ~EnemyController() override;

    void update(QPointF playerPosition);

    EnemyView* getView();

    void takeDamage(int amount);
    bool isAlive() const;

private:
    EnemyModel* model;
    EnemyView* view;

    void controlEnemy(const QPointF& playerPosition);
};

#endif // ENEMYCONTROLLER_H
