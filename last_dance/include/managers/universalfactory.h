#ifndef UNIVERSALFACTORY_H
#define UNIVERSALFACTORY_H

#include "include/textures/itexture.h"
#include "include/textures/texture.h"
#include "include/textures/invisibletexture.h"
#include "include/textures/coinstexture.h"

template <class AbstractProduct, typename IdentifierType, typename DataType>
class UniversalFactory {
public:
    using ProductCreator = std::function<AbstractProduct*(const DataType&)>;

    bool Register(const IdentifierType &id, ProductCreator creator) {
        return associations_.insert({id, creator}).second;
    }

    AbstractProduct* Create(const IdentifierType& id, const DataType& data) {
        auto it = associations_.find(id);
        if (it != associations_.end()) {
            return it->second(data);
        }
        return nullptr;
    }

private:
    std::map<IdentifierType, ProductCreator> associations_;
};

#endif // UNIVERSALFACTORY_H
