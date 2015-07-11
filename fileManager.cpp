#include "fileManager.h"

using namespace std;

vector<string> readWords(std::string filePath, bool debug) {
    ifstream file;
    string word;
    vector<string> wordList;

    file.open(filePath);
    if (!file.is_open()) {
        if (debug) cout << "[ERR] Non è stato possibile aprire il file." << endl;
        // Non ha senso continuare se non possiamo accedere al file col testo necessario
        exit(1);
    } else {
        if (debug) cout << "[DEBUG] File aperto correttamente." << endl;
    }

    // TODO: show progress
    // '>>' separa sugli spazi, non c'è bisogno di loopare manualmente sui caratteri
    while (file >> word) {
        wordList.push_back(word);
    }

    if (debug) {
        cout << "[DEBUG] Numero di parole: " << wordList.size() << endl;
        cout << "[DEBUG] Lista delle parole: \"";
        for (int i = 0; i < wordList.size(); i++) {
            cout << "[DEBUG]";
            if (i != 0) cout << " ";  // previeni spazio precedente alla prima parola
            cout << wordList.at((unsigned long) i);
        }
        cout << "\"" << endl << endl;
    }

    file.close();
    return wordList;
}