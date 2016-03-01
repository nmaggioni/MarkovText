#include "arguments.h"
#include <iostream>
#include <fstream>
#include <sstream>

extern std::string filePath;
extern int wordsNumber;

int markovOrderInt;

bool filePathExists(const char *filename) {
    std::ifstream ifile(filename);
    return (bool) ifile;
}

void checkArguments(int argc, char *argv[]) {
    // TODO: {-h|--help} switch

    // controlla il numero totale dei parametri
    if (argc != 4) {  // filename del programma + 3 parametri
        std::cout << "[ERR] Il numero di parametri forniti non è corretto." << std::endl << std::endl <<
            "Utilizzo: './Markov_Bot fileInput numeroParole precisione'" << std::endl <<
            "'fileInput' è il path al file di testo, 'numeroParole' è il numero di parole da " <<
            "generare (intero), 'precisione' è un intero solitamente compreso tra 1 e 3." << std::endl;
        exit(1);
    }

    char *filePathArgv = argv[1];
    if (!filePathExists(filePathArgv)) {
        std::cout << "[ERR] Il percorso al testo sorgente fornito non è valido." << std::endl;
        exit(1);
    }
    filePath = filePathArgv;

    // controlla se il secondo parametro contiene solo numeri
    char *wordsNumberArgv = argv[2];
    while (*wordsNumberArgv) {
        if (!isdigit(*wordsNumberArgv++)) {
            std::cout << "[ERR] Il numero di parole fornito non è valido." << std::endl;
            exit(1);
        }
    }
    wordsNumber = atoi(argv[2]);

    // controlla se il terzo parametro contiene solo numeri
    char *markovOrderArgv = argv[3];
    while (*markovOrderArgv) {
        if (!isdigit(*markovOrderArgv++)) {
            std::cout << "[ERR] La precisione fornita non è valida." << std::endl;
            exit(1);
        }
    }
    markovOrderInt = atoi(argv[3]);
}

int getPrecision() {
    return markovOrderInt;
}
