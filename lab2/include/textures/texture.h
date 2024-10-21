#ifndef TEXTURE_H
#define TEXTURE_H

#include <QGraphicsPixmapItem>
#include "include/textures/itexture.h"

class Texture : public ITexture {
public:
    Texture(int width, int height, int x, int y, const QString& img);
    Texture(int width, int height, int x, int y);
    enum { Type = UserType + 3 };
    int type() const override;
};

#endif // TEXTURE_H
