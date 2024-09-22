#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "FileManager.h"

using namespace std;

bool FileManager::openInputFile(const string& filePath) {
    inputFile.open(filePath);
    return inputFile.is_open();
}

bool FileManager::openOutputFile(const string& filePath) {
    outputFile.open(filePath);
    return outputFile.is_open();
}

bool FileManager::readLine(string& line) {
    return getline(inputFile, line) ? true : false;
}

void FileManager::writeCSV(const list<pair<string, int>>& sortedWords, int totalWords) {
    for (const auto& pair : sortedWords) {
        double percentage = round(static_cast<double>(pair.second) / totalWords * 100 * 100) / 100;
        outputFile << pair.first << "," << pair.second << "," << percentage << "%\n";
    }
}