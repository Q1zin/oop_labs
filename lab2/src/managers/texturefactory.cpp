#include "include/managers/texturefactory.h"
#include "include/textures/texture.h"
#include "include/textures/invisibletexture.h"
#include "include/textures/coinstexture.h"

ITexture *TextureFactory::create(const QString& textureType, int width, int height, int x, int y, const QString& img) {
    if (textureType == "regular") {
        if (img != "") {
            return new Texture(width, height, x, y, img);
        } else {
            return new Texture(width, height, x, y);
        }

    } else if (textureType == "invisible") {
        return new InvisibleTexture(width, height, x, y, img);
    } else if (textureType == "coin") {
        return new CoinsTexture(x, y);
    } else {
        return nullptr;
    }
}
