#include <QGraphicsPixmapItem>
#include "include/textures/coinstexture.h"

CoinsTexture::CoinsTexture(int x, int y) : ITexture(0) {
    setPixmap(QPixmap("/Users/mir/Realm_of_Rebirth/assets/img/coin.png").scaled(50, 50, Qt::KeepAspectRatio));
    setPos(x, y);
}

int CoinsTexture::type() const { return Type; }
