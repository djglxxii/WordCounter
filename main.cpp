#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "WordCounter.h"

void addWordsFromFile(WordCounter &wc, std::ifstream &file);

void writeToFile(std::string const &filename, std::string const &contents);

int main(int argv, char *argc[]) {
    WordCounter wc = WordCounter();

    if (argv < 2) {
        std::cerr << "no input file specified" << std::endl;
        system("pause");

        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argv; i++) {
        std::string filename = argc[i];
        std::ifstream file(filename);

        if (!file) {
            std::cerr << "Cannot open input file " << filename << std::endl;
            system("pause");

            exit(EXIT_FAILURE);
        } else {
            std::cout << "Reading file '" << filename << "'..." << std::endl;
        }

        addWordsFromFile(wc, file);
    }

    auto rpt = wc.getReport();

    std::string const rptFilename = "WordCount_report.txt";
    writeToFile(rptFilename, rpt);

    std::cout << "Writing report file to '" << rptFilename << "'..." << std::endl;
    std::cout << "DONE!" << std::endl;

    return EXIT_SUCCESS;
}

void addWordsFromFile(WordCounter &wc, std::ifstream &file) {
    std::string word;

    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(remove_if(word.begin(), word.end(), [](int ch) {
            return ch >= 0 && ch <= 255 && ispunct(ch);
        }), word.end());

        wc.addWord(word);
    }
}

void writeToFile(std::string const &filename, std::string const &contents) {
    std::ofstream outfile;
    outfile.open(filename);
    outfile << contents;
    outfile.close();
}
