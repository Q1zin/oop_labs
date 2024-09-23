#include <iostream>
#include <string>
#include <list>
#include <cctype>

#include "TextProcessor.h"

std::list<std::string> TextProcessor::splitWords(const std::string& text) {
    std::list<std::string> words;
    std::string temp;

    for (const char ch : text) {
        if (isalnum(ch))
            temp += std::tolower(ch);
        else if (isspace(ch)) {
            if (temp.length() > 0)
                words.push_back(temp);
            temp = "";
        }
    }

    if (temp.length() > 0)
        words.push_back(temp);

    return words;
}