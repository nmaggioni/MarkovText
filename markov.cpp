#include "markov.h"
#include <chrono>
#include <thread>
#include <sstream>

using namespace std;

string markovText = "";

void markovPrepare(std::string filePath, bool debug) {
    vector<string> wordList = readWords(filePath, debug);
    string twoWords;
    string nextWord;
    int wordCount = 0;
    for (int i = 0; i < (int) wordList.size(); i++) {
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
            if (i < ((int) wordList.size() - 1)) {
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

    cout << endl;
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

/*void capitalizeSentences(char *ptr) {
    int space = 0;
    int period = 0;
    *ptr = (char) toupper(*ptr);
    cout << *ptr;
    for (int i = 1; i < strlen(ptr); i++) {
        if (space == 1 && period == 1) {
            *ptr = (char) toupper(*(ptr + i));
            cout << *ptr;
            period = 0;
            space = 0;
        } else {
            cout << (*(ptr + i));
            if (period == 1) {
                if (*(ptr + i) == ' ') {
                    space = 1;
                } else {
                    period = 0;
                }
            } else {
                if (*(ptr + i) == '.') {
                    period = 1;
                } else {
                    period = 0;
                }
            }
        }
    }
}*/

string markovGetText() {
    markovText[0] = (char) toupper(markovText[0]);  // Capitalizza la prima lettera
    //capitalizeSentences(markovText);
    return markovText;
}