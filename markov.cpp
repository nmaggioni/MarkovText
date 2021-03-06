#include "markov.h"

using namespace std;

dictionaryManager dictManager;
fileManager fManager;

int markovOrderGlobal;
string markovText = "";

void markovPrepare(std::string filePath, int markovOrder) {
    markovOrderGlobal = markovOrder;
    vector<string> wordList = fManager.readWords(filePath);
    int wSize = (int) wordList.size();
    for (int i = 0; i < (wSize - (markovOrder + 1)); i++) {
        cout << "Lettura: " << (i * 100) / (wSize - markovOrder) <<
        "% (parola " << i << " di " << (wSize - markovOrder) << ")" << '\r' << flush;

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
                dictManager.addToDictionary(words, nextWord);
                wSize = (int) wordList.size();
                break;
            }
        }
    }
    cout << "Lettura: 100% (parola " << (wSize - markovOrder) <<
    " di " << (wSize - markovOrder) << ")" << endl;
}

int lastWordsKey(vector<string> words) {
    int wSize = (int) words.size();
    string lastWords = "";

    // prendi le ultime due parole
    if (wSize <= markovOrderGlobal) {  // se non ci sono abastanza parole
        for (int i = 0; i < (wSize - 1); i++) { // prendi tutto
            lastWords.append(words[i] + " ");
        }
        lastWords.append(words[wSize - 1]);
    } else {  // se ci sono abbastanza parole
        int wordCount = 0;
        int curIndex = wSize - markovOrderGlobal;
        while (wordCount < (markovOrderGlobal - 1)) {
            lastWords.append(words[curIndex] + " ");
            curIndex++;
            wordCount++;
        }
        lastWords.append(words[curIndex]);
    }

    vector<dictionary> dict = dictManager.getDictionary();
    for (int keyIndex = 0; keyIndex < ((int) dict.size() - 1); keyIndex++) {
        if (dict[keyIndex].key.find(lastWords) != string::npos) {
            return keyIndex;
        }
    }

    // se arriviamo qui non è stato possibile trovare la chiave successiva
    cout << endl << endl << "[ERR] Non sono stati trovati abbastanza termini coerenti."
            " Varia la precisione o il numero di parole richieste." << endl << "Nota: si"
            " consiglia di mantenere la precisione tra i valori 1 e 3 compresi, precisioni"
            " superiori potrebbero portare alla non-variazione del testo." << endl << endl;
    for (; ;) {
        cout << "Premi [INVIO] per vedere l'ultima scrittura elaborata oppure inserisci [Q] per uscire: ";
        char input = (char) cin.get();
        if (input == 'Q' || input == 'q') {
            exit(1);
        } else if (input == '\n') {
            cout << "================================================"
                    "======================================" << endl;
            for (int i = 0; i < (wSize - 1); i++) {
                cout << words[i] << " ";
            }
            cout << words[wSize - 1] << endl;
            exit(1);
        }
        cout << '\r';
    }
}

void markovCreate(int wordsNumber) {
    vector<dictionary> wordsDictionary = dictManager.getDictionary();
    int dSize = (int) wordsDictionary.size();
    vector<string> result;
    int wordCount = 0;
    int value_index;

    while (wordCount < wordsNumber) {
        cout << "Scrittura: " << (wordCount * 100) / wordsNumber <<
        "% (parola " << wordCount << " di " << wordsNumber << ")" << '\r' << flush;
        int key_index;
        if (wordCount == 0) {
            key_index = rand() % dSize;
        } else {
            key_index = lastWordsKey(result);
        }
        vector<string> values = wordsDictionary[key_index].value;
        int vSize = (int) values.size();
        if (vSize == 1) {
            value_index = 0;
        } else {
            value_index = rand() % vSize;
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
    markovText[0] = (char) toupper(markovText[0]);
    if (markovText[markovText.size() - 1] != '.') {
        markovText += ".";
    }
    return markovText;
}
