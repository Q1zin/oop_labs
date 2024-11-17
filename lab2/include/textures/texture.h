#ifndef TEXTURE_H
#define TEXTURE_H

#include <QGraphicsPixmapItem>
#include "include/textures/itexture.h"

class Texture : public ITexture {
public:
    Texture(const QPoint& position, const QSize& size, const QString& img);
    Texture(const QPoint& position, const QSize& size);
    enum { Type = UserType + 3 };
    int type() const override;
};

#endif // TEXTURE_H
