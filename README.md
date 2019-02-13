# WordCounter

## Overview
The WordCounter program will accept a variable number of input text files and will output a report
that contains a list of all unique words found across the input files combined.  WordCounter will
ignore characters outside of the English alphabet and will ignore puncation (no periods, commas, etc).
Words with hyphens or apostrophes are retained and are considered unique words (e.g. "it's" vs "its" 
are two separate words). Lastly, all words are converted to lower case before processing.

## Usage
To run WordCounter, compile the program and, on at the command prompt, enter:

WordCounter.exe [outputFile] [inputFile1] [inputFile2] [inputFile3] ...

If the input files exist, WordCounter will give a progress update and will output a report file.
The report file will list all the unique words found across the input files and give a 
number of how many times a word was detected, as well as a total unique words summary.

## Technical Details
The implementation of WordCounter uses a custom red-black self-balancing binary tree named "CountingRedBlackTree".
The CountingRedBlackTree uses a special node structure that will keep track of how many times an
element (i.e. word) has been added to the tree.  In other words, if a duplicate value is attempt to be 
added the respective node will have its counter incremented.

The 'update', 'rotateLeft', and 'rotateRight' algorithms are based on code from 
https://www.coders-hub.com/2015/07/red-black-tree-rb-tree-using-c.html that was cutomized for this 
program's use.

Finally, be aware that this program uses C++ 11's "smart pointers" that eliminates the need for
manual memory management.  As per the best practices guidelines, those classes that use smart pointers
**DO NOT** have destructors defined.

## Performance Analysis

### CountingRedBlackTree.cpp

CountingRedBlackTree::int size() const
- returns the number of nodes in the tree
- O(1) complexity

CountingRedBlackTree::bool empty() const
- returns true if tree is empty
- O(1) complexity

CountingRedBlackTree::void insert(T const &elem)
- insert an element into the tree
- O(logn) complexity.
	1. search for a position for the node entry - O(logn) complexity.
	2. if an element already exists then increment counter - O(1) complexity.
	3. if an element does not exist, create new node - O(1) complexity.
	4. finally, a call to update - O(logn) complexity.

CountingRedBlackTree::void update(std::shared_ptr<Node> &p)
- update the tree's node red/blackness.
- O(logn) complexity.
	1. search for nodes that require recoloring - O(logn) complexity.
	2. potential call to rotateLeft() or rotateRight() - O(1) complexity.

CountingRedBlackTree::void rotateLeft(std::shared_ptr<Node> &p)
- rebalance tree routine
- O(1) complexity.

CountingRedBlackTree::void rotateRight(std::shared_ptr<Node> &p)
- rebalance tree routine
- O(1) complexity.

CountingRedBlackTree::void inOrder(std::shared_ptr<Node> v, typename Position::PositionList &pl) const
- in order traveral of the tree
- O(n) complexity.
	1. visits every node in tree - O(n)
	2. for each node, call to std::list push_back() - O(1)
 
CountingRedBlackTree::Position::PositionList CountingRedBlackTree<T>::getPositions() const
- returns a list of positions in-order
- O(n) complexity.
    1. call to inOrder()

### WordCounter.cpp

WordCounter::void addWord(std::string const &word)
- add a word
- O(logn) complexity.
    1. call to CountingRedBlackTree insert()
 
WordCounter::std::string WordCounter::getReport() const
- get word report
- O(n) complexity
    1. call to CountingRedBlackTree getPositions()
  