#include <string>

#include "CountingRedBlackTree.h"

class WordCounter {
public:
    /**
     * Constructor
     */
    WordCounter();

    /**
     * Destructor.
     */
    ~WordCounter();

    /**
     * Add a word.
     * @param The word to add.
     */
    void addWord(std::string const &word);

    /**
     * Get report.
     * @return Returns a report containing unique word counts.
     */
    std::string getReport() const;

private:
    CountingRedBlackTree<std::string> cbt;
};
