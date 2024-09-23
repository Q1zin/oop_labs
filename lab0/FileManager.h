#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <string>
#include <list>

class FileManager {
private:
    std::ifstream inputFile{nullptr};
    std::ofstream outputFile{nullptr};
public:
    bool openInputFile(const std::string& filePath);
    bool openOutputFile(const std::string& filePath);
    bool readLine(std::string& line, bool& err);
    void writeCSV(const std::list<std::pair<std::string, int>>& sortedWords, int totalWords);
};

#endif //FILEMANAGER_H
