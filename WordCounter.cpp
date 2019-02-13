#include <string>
#include <iostream>

#include "WordCounter.h"
#include "CountingRedBlackTree.h"

WordCounter::WordCounter() {
    cbt = CountingRedBlackTree<std::string>();
}

WordCounter::~WordCounter() = default;

void WordCounter::addWord(std::string const &word) {
    cbt.insert(word);
}

std::string WordCounter::getReport() const {
    auto pl = cbt.getPositions();

    std::string rpt;
    int wordCount;

    for (CountingRedBlackTree<std::string>::Position &p :pl) {
        auto node = *p;
        wordCount = node->count;

        rpt.append("\t");
        rpt.append(std::to_string(wordCount));

        // adjust tabbing for count column.
        if (wordCount < 1000) {
            rpt.append("\t\t");
        } else {
            rpt.append("\t");
        }

        rpt.append(node->element);
        rpt.append("\n");
    }

    rpt.append("\t");
    rpt.append("--------------------------");
    rpt.append("\n");
    rpt.append("\t");
    rpt.append(std::to_string(cbt.size()));
    rpt.append("\t");
    rpt.append("Total number of different words");

    return rpt;
}
