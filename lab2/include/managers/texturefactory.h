#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include "include/textures/itexture.h"
#include "include/textures/texture.h"
#include "include/textures/invisibletexture.h"
#include "include/textures/coinstexture.h"

template <class AbstractProduct, typename IdentifierType>
class TextureFactory {
public:
    using ProductCreator = std::function<AbstractProduct*(const QPoint&, const QSize&, const QString&)>;

    bool Register(const IdentifierType &id, ProductCreator creator) {
        return associations_.insert({id, creator}).second;
    }

    AbstractProduct* Create(const IdentifierType& id, const QPoint& position, const QSize& size = QSize(0,0), const QString& img = "") {
        auto it = associations_.find(id);
        if (it != associations_.end()) {
            return it->second(position, size, img);
        }
        return nullptr;
    };

private:
    std::map<IdentifierType, ProductCreator> associations_;
};

#endif // TEXTUREFACTORY_H
