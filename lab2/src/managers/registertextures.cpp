#include "include/managers/texturefactory.h"
#include "include/textures/itexture.h"
#include "include/textures/coinstexture.h"
#include "include/textures/invisibletexture.h"
#include "include/textures/texture.h"

void registerTextures(TextureFactory<ITexture, QString> &factory) {
    factory.Register("regular", [](const QPoint& position, const QSize& size, const QString& img = "") -> ITexture* {
        if (img == "") {
            return new Texture(position, size);
        } else {
            return new Texture(position, size, img);
        }
    });

    factory.Register("invisible", [](const QPoint& position, const QSize& size, const QString& img) -> ITexture* {
        return new InvisibleTexture(position, size, img);
    });

    factory.Register("coin", [](const QPoint& position, [[maybe_unused]] const QSize& size, [[maybe_unused]] const QString& img) -> ITexture* {
        return new CoinsTexture(position);
    });
}
