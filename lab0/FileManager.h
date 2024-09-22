#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <string>
#include <list>

using namespace std;

class FileManager {
private:
    ifstream inputFile{nullptr};
    ofstream outputFile{nullptr};
public:
    bool openInputFile(const string& filePath);
    bool openOutputFile(const string& filePath);
    bool readLine(string& line);
    void writeCSV(const list<pair<string, int>>& sortedWords, int totalWords);
};



#endif //FILEMANAGER_H
