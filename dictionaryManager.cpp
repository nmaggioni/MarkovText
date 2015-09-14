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

vector<dictionary> dictionaryManager::getDictionary() {
    return wordCombinations;
}