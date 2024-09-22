#include <iostream>
#include <string>

#include "FileManager.h"
#include "WordCounter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Error: invalid number of arguments" << endl;
        return 1;
    }

    FileManager fileManager;
    if (!fileManager.openInputFile(argv[1])) {
        cerr << "Error: can't open file " << argv[1] << endl;
        return 1;
    }

    WordCounter wordCounter;
    string line;

    while (fileManager.readLine(line)) {
        wordCounter.processLine(line);
    }

    if (!fileManager.openOutputFile(argv[2])) {
        cerr << "Error: can't open file " << argv[2] << endl;
        return 1;
    }

    fileManager.writeCSV(wordCounter.getSortedWords(), wordCounter.getTotalWords());

    return 0;
}
