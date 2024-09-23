#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <string>
#include <list>

class TextProcessor {
public:
    static std::list<std::string> splitWords(const std::string& text);
};

#endif //TEXTPROCESSOR_H
