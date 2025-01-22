#include "include/entities/controller/enemycontroller.h"

EnemyController::EnemyController(EnemyModel *model, EnemyView *view, QObject *parent)
    : EntityController(model, view, parent), model(model), view(view) {}

EnemyController::~EnemyController() {
    delete model;
    delete view;
}

void EnemyController::update(QPointF playerPosition) {
    if (!model->isAlive()) return;

    EntityController::update();

    controlEnemy(playerPosition);
}

EnemyView *EnemyController::getView() {
    return view;
}

void EnemyController::controlEnemy(const QPointF &playerPosition) {
    QPointF enemyPosition = getPosition();
    QPointF oldVelocity = model->getVelocity();
    if (std::abs(playerPosition.x() - enemyPosition.x()) < 5) {
        model->setVelocity(QPointF(0, oldVelocity.y()));
        return;
    };

    if (playerPosition.x() < enemyPosition.x())
        oldVelocity.setX(-2);

    if (playerPosition.x() > enemyPosition.x())
        oldVelocity.setX(2);

    if (playerPosition.y() < enemyPosition.y() && model->getVelocity() != oldVelocity)
        if (model->getIsOnGround())
            oldVelocity.setY(-18);

    model->setVelocity(oldVelocity);
}

void EnemyController::takeDamage(int amount) {
    model->takeDamage(amount);
}

bool EnemyController::isAlive() const {
    return model->isAlive();
}