#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "include/entities/model/entitymodel.h"
#include "include/textures/texture.h"

class PlayerModel : public EntityModel {
    Q_OBJECT

public:
    explicit PlayerModel(QPointF position, QObject* parent = nullptr);

    int getDirection() const;
    void setDirection(int dir);

private:
    int direction = 1; // 1 - вправо, -1 - влево
};


#endif // PLAYERMODEL_H
