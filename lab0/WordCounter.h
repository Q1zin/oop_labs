#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>
#include <list>
#include <map>

class WordCounter {
private:
    std::map<std::string, int> wordCount{};
    int totalWords{0};
public:
    void addWords(const std::list<std::string>& words);
    void processLine(std::string& line);
    std::list<std::pair<std::string, int>> getSortedWords();
    int getTotalWords() const;
};

#endif