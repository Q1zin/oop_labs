#include <iostream>
#include <string>

#include "FileManager.h"
#include "WordCounter.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: invalid number of arguments" << std::endl;
        return 1;
    }

    FileManager fileManager;
    if (!fileManager.openInputFile(argv[1])) {
        std::cerr << "Error: can't open file " << argv[1] << std::endl;
        return 2;
    }

    WordCounter wordCounter;
    std::string line;
    bool errReadFile = false;

    while (fileManager.readLine(line, errReadFile)) {
        wordCounter.processLine(line);
    }

    if (errReadFile) {
        std::cerr << "Error: can't read line in file" << std::endl;
        return 3;
    }

    if (!fileManager.openOutputFile(argv[2])) {
        std::cerr << "Error: can't open file " << argv[2] << std::endl;
        return 4;
    }

    fileManager.writeCSV(wordCounter.getSortedWords(), wordCounter.getTotalWords());

    return 0;
}
