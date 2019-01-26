#include <string>
#include <iostream>

#include "WordCounter.h"
#include "CountingBinaryTree.h"

WordCounter::WordCounter() {
    cbt = CountingBinaryTree<std::string>();
}

WordCounter::~WordCounter() = default;

void WordCounter::addWord(std::string const &word) {
    cbt.insert(word);
}

std::string WordCounter::getReport() const {
    const std::string TAB = "\t";
    const std::string LF = "\n";

    auto pl = cbt.getPositions();

    std::string rpt;

    for (CountingBinaryTree<std::string>::Position &p :pl) {
        auto node = *p;

        rpt.append(TAB);
        rpt.append(std::to_string(node->count));
        rpt.append(TAB).append(TAB).append(TAB).append(TAB);
        rpt.append(node->element);
        rpt.append(LF);
    }

    rpt.append(TAB);
    rpt.append("--------------------------");
    rpt.append(LF);
    rpt.append(TAB);
    rpt.append(std::to_string(cbt.size()));
    rpt.append(TAB).append(TAB).append(TAB);
    rpt.append("Total number of different words");

    return rpt;
}
