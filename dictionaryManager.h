#ifndef MARKOV_BOT_DICTIONARYMANAGER_H
#define MARKOV_BOT_DICTIONARYMANAGER_H

#include "dictionary.h"

void addToDictionary(std::string key, std::string value);

void printDictionary();

std::vector<dictionary> getDictionary();

#endif //MARKOV_BOT_DICTIONARYMANAGER_H
