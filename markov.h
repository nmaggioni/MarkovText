#ifndef MARKOV_BOT_MARKOV_H
#define MARKOV_BOT_MARKOV_H

#include "dictionaryManager.h"
#include "fileManager.h"

const int markovOrder = 3;

void markovPrepare(std::string filePath, bool debug);

void markovCreate(int wordsNumber);

std::string markovGetText();

#endif //MARKOV_BOT_MARKOV_H
