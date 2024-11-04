#include <QGraphicsPixmapItem>
#include <QUrl>
#include <QPixmap>
#include "include/textures/coinstexture.h"

CoinsTexture::CoinsTexture(const QPoint& position) : ITexture(0) {
    setPixmap(QPixmap(":/img/coin.png").scaled(50, 50, Qt::KeepAspectRatio));
    setPos(position.x(), position.y());
}

int CoinsTexture::type() const { return Type; }
