#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include "include/textures/itexture.h"
#include "include/textures/texture.h"
#include "include/textures/invisibletexture.h"
#include "include/textures/coinstexture.h"


class TextureFactory {
public:
    static ITexture* create(const QString& textureType, const QPoint& position = QPoint(0, 0), const QSize& size = QSize(0, 0), const QString& img = "");
};
#endif // TEXTUREFACTORY_H
