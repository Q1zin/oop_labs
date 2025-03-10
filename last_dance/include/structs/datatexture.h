#ifndef DATATEXTURE
#define DATATEXTURE

#include <QPoint>
#include <QSize>
#include <QString>

struct dataTexture {
    QPoint position;
    QSize size = QSize(0, 0);
    QString img = "";
};

#endif
