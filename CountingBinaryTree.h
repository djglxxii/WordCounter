#pragma once

#include <memory>
#include <list>
#include <utility>

enum Color {
    RED,
    BLACK
};

/**
 * The 'CountingBinaryTree' is a self balancing Red-Black binary tree.
 * Additionally, it will keep track of a count of how many times an element
 * has been added to the tree.
 */
template<typename T>
class CountingBinaryTree {
public:
    struct Node {
        Node(T e) : element(std::move(e)), count(1), color(RED) {}

        T element;
        int count;
        Color color;

        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        /**
         * Operator to return element.
         * @return
         */
        T const &operator*() const { return element; }

        /**
         * Operator to increment counter.
         */
        void operator++() { count++; }

        /**
         * Operator to decrement counter.
         */
        void operator--() { count--; }

        /**
         * Is this a root node?
         * @return True if this node has no parent. False otherwise.
         */
        bool isRoot() const { return parent == nullptr; }

        /**
         * Does this node have a left child node?
         * @return True if left child node exist, false otherwise.
         */
        bool hasLeft() const { return left != nullptr; }

        /**
         * Does this node have a right child node?
         * @return True if right child node exist, false otherwise.
         */
        bool hasRight() const { return right != nullptr; }
    };

public:
    class Position {
    public:
        Position(std::shared_ptr<Node> node) : n(std::move(node)) {}

        /**
         * Operator to return node.
         * @return The node.
         */
        std::shared_ptr<Node> const &operator*() const { return n; }

        /**
         * Position containing the parent node.
         * @return
         */
        Position parent() { return Position(n->parent); }

        /**
         * Is the position the root?
         * @return True if root, false otherwise.
         */
        bool isRoot() const { return n->isRoot(); }

        /**
         * The left position.
         * @return The left position.
         */
        Position left() { return Position(n->left); }

        /**
         * Does this position have a left child position?
         * @return True if left child position exists.
         */
        bool hasLeft() const { return n->hasLeft(); }

        Position right() { return Position(n->right); }

        bool hasRight() const { return n->hasRight(); }

        typedef std::list<Position> PositionList;

        friend class CountingBinaryTree<T>;

    private:
        // this position's node.
        std::shared_ptr<Node> n;
    };

public:
    CountingBinaryTree();

    /**
     * Size of the tree.
     * @return The number of nodes in the tree.
     */
    int size() const { return n; }

    /**
     * Is the tree empty?
     * @return True if no nodes exists, false otherwise.
     */
    bool empty() const { return n == 0; }

    /**
     * Insert an element.
     * @param elem The element to insert.
     */
    void insert(T const &elem);

    typename Position::PositionList getPositions() const;

private:
    // update the tree red/blackness
    void update(std::shared_ptr<Node> &p);

    // perform a left rotation around p.
    void rotateLeft(std::shared_ptr<Node> &p);

    // perform a right rotation around p.
    void rotateRight(std::shared_ptr<Node> &p);

    // perform an inorder traversal, populating the provided position list.
    void inorder(std::shared_ptr<Node> v, typename Position::PositionList &pl) const;

    // root node.
    std::shared_ptr<Node> root;

    // the node count.
    int n;
};
