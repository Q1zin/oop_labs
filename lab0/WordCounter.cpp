#include <string>
#include <list>
#include <map>

#include "WordCounter.h"
#include "TextProcessor.h"

void WordCounter::addWords(const std::list<std::string>& words) {
    for (const auto& word : words) {
        ++wordCount[word];
        ++totalWords;
    }
}

void WordCounter::processLine(std::string& line) {
    std::list<std::string> words = TextProcessor::splitWords(line);
    addWords(words);
}

std::list<std::pair<std::string, int>> WordCounter::getSortedWords() {
    std::list<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());
    sortedWords.sort([](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        return b.second < a.second;
    });
    return sortedWords;
}

int WordCounter::getTotalWords() const {
    return totalWords;
}
