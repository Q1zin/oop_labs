#ifndef REGISTERTEXTURES_H
#define REGISTERTEXTURES_H

#include "include/managers/texturefactory.h"
#include "include/textures/itexture.h"

void registerTextures(TextureFactory<ITexture, QString>& factory);

#endif // REGISTERTEXTURES_H
