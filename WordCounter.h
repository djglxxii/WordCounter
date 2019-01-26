#include <string>

#include "CountingBinaryTree.h"

class WordCounter {
public:
    WordCounter();

    ~WordCounter();

    void addWord(std::string const &word);

    std::string getReport() const;

private:
    CountingBinaryTree<std::string> cbt;
};
