#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <string>
#include <list>

using namespace std;

class TextProcessor {
private:
    static string str_tolower(string s);
public:
    static string removePunctuation(const string& text);
    static list<string> split(const string& text, char sep);
};



#endif //TEXTPROCESSOR_H
