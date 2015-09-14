#ifndef MARKOV_BOT_FILEMANAGER_H
#define MARKOV_BOT_FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>

class fileManager {
public:
    std::vector<std::string> readWords(std::string filePath);
};

#endif //MARKOV_BOT_FILEMANAGER_H
