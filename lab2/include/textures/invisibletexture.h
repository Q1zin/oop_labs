#ifndef INVISIBLETEXTURE_H
#define INVISIBLETEXTURE_H

#include <QGraphicsPixmapItem>
#include "include/textures/itexture.h"

class InvisibleTexture : public ITexture {
public:
    InvisibleTexture(const QPoint& position, const QSize& size, const QString& img);
    enum { Type = UserType + 4 };
    int type() const override;
};

#endif // INVISIBLETEXTURE_H
