#ifndef INVISIBLETEXTURE_H
#define INVISIBLETEXTURE_H

#include <QGraphicsPixmapItem>
#include "include/textures/itexture.h"

class InvisibleTexture : public ITexture {
public:
    InvisibleTexture(int width, int height, int x, int y, const QString& img);
    enum { Type = UserType + 4 };
    int type() const override;
};

#endif // INVISIBLETEXTURE_H
