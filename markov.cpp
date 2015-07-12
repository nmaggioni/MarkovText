#include "markov.h"

using namespace std;

string markovText = "";

void markovPrepare(std::string filePath, bool debug) {
    vector<string> wordList = readWords(filePath, debug);
    for (int i = 0; i < (int) (wordList.size() - (markovOrder + 1)); i++) {
        cout << "Lettura: " << (i * 100) / (wordList.size() - markovOrder) <<
        "% (parola " << i << " di " << (wordList.size() - markovOrder) << ")" << '\r' << flush;

        string words = "";
        string nextWord = "";
        int wordCount = 0;
        while (true) {
            if (wordCount < (markovOrder - 1)) {
                words.append(wordList[i + wordCount]);
                words.append(" ");
                wordCount++;
            } else {
                words.append(wordList[i + wordCount]);
                nextWord = wordList[i + wordCount + 1];
                addToDictionary(words, nextWord);
                break;
            }
        }
    }
    cout << "Lettura: 100% (parola " << (wordList.size() - markovOrder) <<
    " di " << (wordList.size() - markovOrder) << ")" << endl;

    if (debug) {
        printDictionary();
    }
}

void err_noTerms() {
    cout << endl << endl << "[ERROR] Non sono stati trovati abbastanza"
            " termini coerenti. Diminuisci la precisione"
            " o il numero di parole richieste." << endl;
    exit(1);
}

int lastWordsKey(vector<string> words) {
    // genera stringa delle ultime parole
    int index = (int) words.size() - 1;
    string lastWords;
    for (int wordCount = 0; wordCount < (markovOrder - 1) && wordCount < ((int) words.size() - 1); wordCount++) {
        lastWords.append(words[index]);
        lastWords.append(" ");
        index--;
    }
    lastWords.append(words[index]);

    // cerca nel dizionario una chiave che contenga le ultime parole
    for (int i = 0; i < (int) getDictionary().size(); i++) {
        if (getDictionary()[i].key.find(lastWords) != string::npos) {
            return i;
        }
    }
    err_noTerms();
    return -1;
}

void markovCreate(int wordsNumber) {
    vector<dictionary> wordsDictionary = getDictionary();
    vector<string> result;
    int value_index;
    int wordCount = 0;

    while (wordCount < wordsNumber) {
        cout << "Scrittura: " << (wordCount * 100) / wordsNumber <<
        "% (parola " << wordCount << " di " << wordsNumber << ")" << '\r' << flush;
        int key_index;
        if (wordCount == 0) {  // la prima parola è casuale
            key_index = rand() % (int) wordsDictionary.size();
        } else {
            key_index = lastWordsKey(result);
        }
        vector<string> values = wordsDictionary[key_index].value;
        if (values.size() > 1) {
            value_index = rand() % (int) values.size();
        } else {
            value_index = 0;
        }
        result.push_back(values[value_index]);
        wordCount++;
    }

    /*while (wordCount < wordsNumber) {
        cout << "Scrittura: " << (wordCount * 100) / wordsNumber <<
        "% (parola " << wordCount << " di " << wordsNumber << ")" << '\r' << flush;

        // concatena contestualmente le successive parole
        int curIndex = (int) result.size() - 1;
        int wordBuildCount = 0;
        string buildKey = lastWords();
        int buildIndex = -1;
        for (int i = 0; i < (int) wordsDictionary.size(); i++) {
            if (wordsDictionary[i].key == buildKey) {
                buildIndex = i;
                break;
            }
        }
        if (buildIndex != -1) {
            vector<string> buildValues = wordsDictionary[buildIndex].value;
            if (buildValues.size() > 1) {
                value_index = rand() % (int) buildValues.size();
            } else {
                value_index = 0;
            }
            result.push_back(buildValues[value_index]);
            wordCount++;
        } else {
            cout << endl << endl << "[ERROR] Non sono stati trovati abbastanza termini coerenti. Diminuisci"
                    " la precisione o il numero di parole richieste." << endl;
            //break; // quit building if no matches
            exit(1);
        }
    }*/

    string resultStr = "";
    for (int i = 0; i < (int) (result.size() - 1); i++) {
        resultStr += (result[i] + " ");
    }
    resultStr += (result[result.size() - 1] + ".");
    cout << "Scrittura: 100% (parola " << wordCount << " di " << wordsNumber << ")" << endl;
    markovText = resultStr;
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