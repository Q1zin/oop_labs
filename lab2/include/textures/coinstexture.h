#ifndef COINSTEXTURE_H
#define COINSTEXTURE_H

#include <QGraphicsPixmapItem>
#include "include/textures/itexture.h"

class CoinsTexture : public ITexture {
public:
    CoinsTexture(const QPoint& position);
    enum { Type = UserType + 5 };
    int type() const override;
};


#endif // COINSTEXTURE_H
