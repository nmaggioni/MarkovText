#include "markov.h"
#include <algorithm>
#include <sstream>
#include <iterator>

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
    string lastWords = "";

    // prendi le ultime due parole
    if ((int) words.size() <= markovOrder) {  // se non ci sono abastanza parole
        for (int i = 0; i < ((int) words.size() - 1); i++) { // prendi tutto
            lastWords.append(words[i] + " ");
        }
        lastWords.append(words[(int) words.size() - 1]);
    } else {  // se ci sono abbastanza parole
        int wordCount = 0;
        int curIndex = ((int) words.size() - 1) - markovOrder;
        while (wordCount < (markovOrder - 1)) {
            lastWords.append(words[curIndex] + " ");
            curIndex++;
            wordCount++;
        }
        lastWords.append(words[curIndex]);
    }

    vector<dictionary> dict = getDictionary();
    for (int keyIndex = 0; keyIndex < ((int) dict.size() - 1); keyIndex++) {
        if (dict[keyIndex].key.find(lastWords) != string::npos) {
            return keyIndex;
        }
    }
    err_noTerms();
    return -1;
}

void markovCreate(int wordsNumber) {
    vector<dictionary> wordsDictionary = getDictionary();
    vector<string> result;
    int wordCount = 0;
    int value_index;

    while (wordCount < wordsNumber) {
        cout << "Scrittura: " << (wordCount * 100) / wordsNumber <<
        "% (parola " << wordCount << " di " << wordsNumber << ")" << '\r' << flush;
        int key_index;
        if (wordCount == 0) {
            key_index = rand() % (int) wordsDictionary.size();
        } else {
            key_index = lastWordsKey(result);
        }
        vector<string> values = wordsDictionary[key_index].value;
        if (values.size() == 1) {
            value_index = 0;
        } else {
            value_index = rand() % (int) values.size();
        }
        result.push_back(values[value_index]);
        wordCount++;
    }

    int finalIndex = 0;
    for (int i = 0; i < ((int) result.size() - 1); i++) {
        markovText += (result[i] + " ");
        finalIndex++;
    }
    cout << "Scrittura: 100% (parola " << wordCount << " di " << wordsNumber << ")" << endl;
    markovText += (result[finalIndex]);
}

string markovGetText() {
    markovText[0] = (char) toupper(markovText[0]);  // Capitalizza la prima lettera
    //capitalizeSentences(markovText);
    return markovText;
}