#include <QGraphicsPixmapItem>
#include "include/textures/texture.h"

Texture::Texture(int width, int height, int x, int y, const QString& img) : ITexture(0){
    setPixmap(QPixmap(img).scaled(width, height, Qt::KeepAspectRatio));
    setPos(x, y);
}

Texture::Texture(int width, int height, int x, int y) : ITexture(0){
    QPixmap pixmap(width, height);
    pixmap.fill("#097100");
    setPixmap(pixmap);
    setPos(x, y);
}

int Texture::type() const { return Type; }
