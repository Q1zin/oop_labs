#include "include/entities/model/playermodel.h"

PlayerModel::PlayerModel(QPointF position, QObject *parent)
    : EntityModel(position, parent) {}

int PlayerModel::getDirection() const { return direction; }

void PlayerModel::setDirection(int dir) { direction = dir; }
