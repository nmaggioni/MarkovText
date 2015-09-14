#ifndef MARKOV_BOT_DICTIONARYMANAGER_H
#define MARKOV_BOT_DICTIONARYMANAGER_H

#include "dictionary.h"

class dictionaryManager {

public:
    void addToDictionary(std::string key, std::string value);

    std::vector<dictionary> getDictionary();

private:
    void printDictionary();
};

#endif //MARKOV_BOT_DICTIONARYMANAGER_H
