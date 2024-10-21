#include <QGraphicsPixmapItem>
#include "include/textures/invisibletexture.h"

InvisibleTexture::InvisibleTexture(int width, int height, int x, int y, const QString& img) : ITexture(0){
    setPixmap(QPixmap(img).scaled(width, height, Qt::KeepAspectRatio));
    setPos(x, y);
}

int InvisibleTexture::type() const { return Type; }
