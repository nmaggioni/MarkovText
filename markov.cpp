#include "markov.h"

using namespace std;

void markovPrepare(std::string filePath, bool debug) {
    vector<string> wordList = readWords(filePath, debug);
    string twoWords;
    string nextWord;
    int wordCount = 0;
    for (int i = 0; i < wordList.size(); i++) {
        // prima parola
        if (wordCount == 0) {
            twoWords.append(wordList[i]);
            twoWords.append(" ");
            wordCount++;
            continue;
        }

        // seconda parola
        if (wordCount == 1) {
            twoWords.append(wordList[i]);

            // valore corrispondente alle due parole
            if (i < (wordList.size() - 1)) {
                // prossima parola (le due parole correnti non sono le ultime)
                nextWord = wordList[i + 1];
                addToDictionary(twoWords, nextWord);
            } else {
                // uso il carattere '.' (le due parole correnti sono le ultime)
                if (twoWords.back() == '.') {
                    twoWords = twoWords.substr(0, twoWords.size() - 1);
                }
                addToDictionary(twoWords, ".");
            }

            wordCount = 0;
            twoWords.clear();
        }
    }

    if (debug) {
        printDictionary();
    }
}

void markovCreate(int wordsNumber, bool debug) {

    //vector<dictionary> foo = getDictionary();
    return;
}

std::string markovPrint() {
    return "foo";
}