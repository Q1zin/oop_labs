#include "include/entities/controller/entitycontroller.h"

EntityController::EntityController(EntityModel *model, EntityView *view, QObject *parent) : QObject(parent), model(model), view(view) {
    connect(model, &EntityModel::positionChanged, view, &EntityView::updatePosition);
}

QPointF EntityController::getPosition() const { return model->getPosition(); }

void EntityController::setPosition(const QPointF &pos) { model->setPosition(pos); }

QPointF EntityController::getVelocity() const { return model->getVelocity(); }

void EntityController::setVelocity(const QPointF &vel) { model->setVelocity(vel); }

void EntityController::update() {
    model->move(view->getPredictCollision(model->getVelocity()));
}


