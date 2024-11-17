#include <QGraphicsPixmapItem>
#include "include/textures/texture.h"

Texture::Texture(const QPoint& position, const QSize& size, const QString& img) : ITexture(0){
    setPixmap(QPixmap(img).scaled(size.width(), size.height(), Qt::KeepAspectRatio));
    setPos(position.x(), position.y());
}

Texture::Texture(const QPoint& position, const QSize& size) : ITexture(0){
    QPixmap pixmap(size.width(), size.height());
    pixmap.fill("#097100");
    setPixmap(pixmap);
    setPos(position.x(), position.y());
}

int Texture::type() const { return Type; }
