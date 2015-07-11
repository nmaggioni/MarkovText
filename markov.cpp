#include "markov.h"
#include <chrono>
#include <thread>

using namespace std;

string markovText = "";

void markovPrepare(std::string filePath, bool debug) {
    vector<string> wordList = readWords(filePath, debug);
    string twoWords;
    string nextWord;
    int wordCount = 0;
    for (int i = 0; i < wordList.size(); i++) {
        cout << "Leggendo parola " << i << " di " << wordList.size() << '\r';

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
                cout << "Leggendo parola " << (i + 1) << " di " << wordList.size() << endl;
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

void markovCreate(int wordsNumber) {
    vector<dictionary> wordsDictionary = getDictionary();
    string result;

    int key_roll;
    int value_roll;
    for (int i = 0; i < wordsNumber; i++) {
        cout << "Scrivendo parola " << i << " di " << wordsNumber << '\r';

        key_roll = rand() % (int) wordsDictionary.size(); // generates number in the range 0..wordsDictionary.size()
        vector<string> values = wordsDictionary[key_roll].value;

        if (values.size() != 1) {  // non c'è bisogno di un indice random se c'è un solo valore
            // generates number in the range 1..wordsDictionary[key_roll].value.size()
            value_roll = rand() % (int) wordsDictionary[key_roll].value.size();
        } else {
            value_roll = 0;
        }

        result.append(values[value_roll]);
        if (i != (wordsNumber - 1)) {
            result.append(" ");
        } else {
            cout << "Scrivendo parola " << i + 1 << " di " << wordsNumber << endl;
            result.append(".");
        }
    }

    markovText = result;
}

string markovGetText() {
    return markovText;
}