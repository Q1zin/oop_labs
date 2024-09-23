#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "FileManager.h"

bool FileManager::openInputFile(const std::string& filePath) {
    inputFile.open(filePath);
    return inputFile.is_open();
}

bool FileManager::openOutputFile(const std::string& filePath) {
    outputFile.open(filePath);
    return outputFile.is_open();
}

bool FileManager::readLine(std::string& line, bool& err) {
    const auto& state = getline(inputFile, line);
    if (inputFile.bad())
        err = true;
    return state ? true : false;
}

void FileManager::writeCSV(const std::list<std::pair<std::string, int>>& sortedWords, int totalWords) {
    for (const auto& pair : sortedWords) {
        double percentage = round(static_cast<double>(pair.second) / totalWords * 100 * 100) / 100;
        outputFile << pair.first << "," << pair.second << "," << percentage << "%\n";
    }
}