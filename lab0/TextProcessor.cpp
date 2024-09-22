#include <iostream>
#include <string>
#include <list>
#include <cctype>
#include "TextProcessor.h"

using namespace std;

string TextProcessor::str_tolower(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return tolower(c); });
    return s;
}

string TextProcessor::removePunctuation(const string& text) {
    string result = text;
    int lenStr = result.length() - 1;
    for (int i = lenStr; i >= 0; i--) {
        char ch = text[i];
        if (!(isalnum(ch) || isspace(ch)) && 
            !((ch == '-' || ch == '\'') && 
            i > 0 && i < lenStr && 
            isalnum(text[i-1]) && isalpha(text[i+1])))
            result.erase(i, 1);
    }
    return result;
}

list<string> TextProcessor::split(const string& text, char sep) {
    list<string> words;
    string temp;
    for (const char c : text) {
        if (c != sep) {
            temp += c;
        } else {
            if (temp.length() > 0)
                words.push_back(str_tolower(temp));
            temp = "";
        }
    }
    if (temp.length() > 0)
        words.push_back(str_tolower(temp));
    return words;
}