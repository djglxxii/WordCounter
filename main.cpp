#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "WordCounter.h"

void addWordsFromFile(WordCounter &wc, std::ifstream &file);

void writeToFile(std::string const &filename, std::string const &contents);

int main(int argc, char *argv[]) {
    WordCounter wc = WordCounter();
    std::string outfile;

    if (argc < 2) {
        std::cerr << "no input file(s) specified" << std::endl;
        system("pause");

        exit(EXIT_FAILURE);
    }

    outfile = argv[1];

    for (int i = 2; i < argc; i++) {
        std::string filename = argv[i];
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

    writeToFile(outfile, rpt);

    std::cout << "Writing report file '" << outfile << "'..." << std::endl;
    std::cout << "DONE!" << std::endl;

    return EXIT_SUCCESS;
}

/**
 * Parse words from file and add them to the WordCounter.
 * @param wc The reference to the WordCounter instance.
 * @param file The file to parse.
 */
void addWordsFromFile(WordCounter &wc, std::ifstream &file) {
    std::string word;

    // filter to only allow alpha characters, hyphens, and apostrophes.
    auto filter = [](int ch) { return ch != 45 && ch != 39 && (ch < 97 || ch > 122); };
    
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(remove_if(word.begin(), word.end(), filter), word.end());

        // string could be empty after the above erase operation.
        if (!word.empty()) {
            wc.addWord(word);
        }
    }
}

/**
 * Write contents to file.
 * @param filename The name of the file to create.
 * @param contents The contents to be written.
 */
void writeToFile(std::string const &filename, std::string const &contents) {
    std::ofstream outfile;

    outfile.open(filename);
    outfile << contents;
    outfile.close();
}
