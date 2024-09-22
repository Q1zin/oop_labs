#include <string>
#include <list>
#include <map>
#include "WordCounter.h"
#include "TextProcessor.h"

using namespace std;

void WordCounter::addWords(const list<string>& words) {
    for (const auto& word : words) {
        ++wordCount[word];
        ++totalWords;
    }
}

void WordCounter::processLine(string& line) {
    list<string> words = TextProcessor::split(TextProcessor::removePunctuation(line), ' ');
    for (const auto& word : words) {
        ++wordCount[word];
        ++totalWords;
    }
}

list<pair<string, int>> WordCounter::getSortedWords() {
    list<pair<string, int>> sortedWords(wordCount.begin(), wordCount.end());
    sortedWords.sort([](const pair<string, int> &a, const pair<string, int> &b) {
        return b.second < a.second;
    });
    return sortedWords;
}

int WordCounter::getTotalWords() const {
    return totalWords;
}
