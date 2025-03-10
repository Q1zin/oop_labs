#include <QGraphicsPixmapItem>
#include "include/textures/invisibletexture.h"

InvisibleTexture::InvisibleTexture(const QPoint& position, const QSize& size, const QString& img) : ITexture(0){
    setPixmap(QPixmap(img).scaled(size.width(), size.height(), Qt::KeepAspectRatio));
    setPos(position.x(), position.y());
}

int InvisibleTexture::type() const { return Type; }
