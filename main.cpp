/*
 *                            The MIT License (MIT)
 *
 *                     Copyright (c) 2015 Niccolò Maggioni
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "markov.h"

const bool debug = true;

std::string filePath;
int wordsNumber;

void checkArguments(int argc, char *argv[]) {
    if (argc != 3) {  // 2 paremetri, il primo è sempre il filename del programma
        std::cout << "[ERR] Il numero di parametri non è corretto." << std::endl;
        exit(1);
    }
    if (argv[1]) {
        //
    }
}

int main(int argc, char *argv[]) {
    checkArguments(argc, argv);

    markovPrepare(filePath, debug);
    markovCreate(wordsNumber, debug);
    markovPrint();

    return 0;
}