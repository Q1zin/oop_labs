#ifndef ITEXTURE_H
#define ITEXTURE_H

#include <QGraphicsPixmapItem>

class ITexture : public QGraphicsPixmapItem {
public:
    ITexture(QGraphicsPixmapItem* parent = nullptr);
    virtual ~ITexture() = default;
    virtual int type() const = 0;
};

#endif // ITEXTURE_H
