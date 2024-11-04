#include "include/managers/texturefactory.h"
#include "include/textures/texture.h"
#include "include/textures/invisibletexture.h"
#include "include/textures/coinstexture.h"

ITexture *TextureFactory::create(const QString& textureType, const QPoint& position, const QSize& size, const QString& img) {
    if (textureType == "regular") {
        if (img != "") {
            return new Texture(position, size, img);
        } else {
            return new Texture(position, size);
        }

    } else if (textureType == "invisible") {
        return new InvisibleTexture(position, size, img);
    } else if (textureType == "coin") {
        return new CoinsTexture(position);
    } else {
        return nullptr;
    }
}
