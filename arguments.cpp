#include "arguments.h"
#include <iostream>
#include <fstream>
#include <sstream>

extern std::string filePath;
extern int wordsNumber;

bool filePathExists(const char *filename) {
    std::ifstream ifile(filename);
    return (bool) ifile;
}

void checkArguments(int argc, char *argv[]) {
    // TODO: {-h|--help} switch

    // controlla il numero totale dei parametri
    if (argc != 3) {  // 2 parametri, il primo è sempre il filename del programma
        std::cout << "[ERR] Il numero di parametri forniti non è corretto." << std::endl;
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
}