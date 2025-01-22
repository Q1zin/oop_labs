#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include <QObject>
#include "include/entities/model/entitymodel.h"
#include "include/entities/view/entityview.h"

class EntityController : public QObject {
    Q_OBJECT

protected:
    EntityModel* model;
    EntityView* view;

public:
    explicit EntityController(EntityModel* model, EntityView* view, QObject* parent = nullptr);

    QPointF getPosition() const;
    void setPosition(const QPointF& pos);

    QPointF getVelocity() const;
    void setVelocity(const QPointF& vel);

    virtual void update();
};

#endif // ENTITYCONTROLLER_H
