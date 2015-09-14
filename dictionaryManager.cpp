#include "dictionaryManager.h"

using namespace std;

struct dictionary entry;
vector<dictionary> wordCombinations;

void dictionaryManager::addToDictionary(string key, string value) {
    int wSize = (int) wordCombinations.size();

    if (wSize == 0) {
        // il dizionario non contiene ancora nessuna chiave
        entry.key = key;
        vector<string> valueVector = {value};
        entry.value = valueVector;
        wordCombinations.push_back(entry);

    } else {

        // il dizionario contiene già delle chiavi
        for (int i = 0; i < wSize; i++) {
            if (wordCombinations[i].key == key) {
                // la chiave esiste già
                wordCombinations[i].value.push_back(value);
                break;
            }
            if (i == wSize - 1) {  // siamo all'ultima chiave
                // la chiave non esiste ancora
                entry.key = key;
                vector<string> valueVector = {value};
                entry.value = valueVector;
                wordCombinations.push_back(entry);
                break;
            }
            wSize = (int) wordCombinations.size();
        }
    }
}

void dictionaryManager::printDictionary() {
    // stampa la chiave e apri le virgolette
    for (int i = 0; i < (int) wordCombinations.size(); i++) {
        cout << "\"" << wordCombinations[i].key << "\" => \"";

        // stampa i valori separati da virgole
        for (int el = 0; el < (int) wordCombinations[i].value.size(); el++) {
            cout << wordCombinations[i].value[el];
            if (el != (int) wordCombinations[i].value.size() - 1) {  // evita la virgola dopo l'ultimo valore
                cout << ", ";
            }
        }

        // chiudi le virgolette a inserisci newline
        cout << "\"" << endl;
    }
}

vector<dictionary> dictionaryManager::getDictionary() {
    return wordCombinations;
}