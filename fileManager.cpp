#include "fileManager.h"

using namespace std;

vector<string> fileManager::readWords(std::string filePath) {
    ifstream file;
    string word;
    vector<string> wordList;

    file.open(filePath);
    if (!file.is_open()) {
        // Non ha senso continuare se non possiamo accedere al file col testo necessario
        exit(1);
    }

    // TODO: show progress
    // '>>' separa sugli spazi, non c'è bisogno di loopare manualmente sui caratteri
    while (file >> word) {
        wordList.push_back(word);
    }

    return wordList;
}