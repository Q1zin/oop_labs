#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>
#include <list>
#include <map>

using namespace std;

class WordCounter {
private:
    map<string, int> wordCount{};
    int totalWords{0};
public:
    void addWords(const list<string>& words);
    void processLine(string& line);
    list<pair<string, int>> getSortedWords();
    int getTotalWords() const;
};

#endif