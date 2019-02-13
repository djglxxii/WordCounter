/**
 * CountingBinaryTree implementation.  'update', 'rotateLeft', and 'rotateRight' algorithms based on
 * code from https://www.coders-hub.com/2015/07/red-black-tree-rb-tree-using-c.html
 */
#include <memory>

#include "CountingRedBlackTree.h"

template<typename T>
CountingRedBlackTree<T>::CountingRedBlackTree() :n(0) {}

template<typename T>
void CountingRedBlackTree<T>::insert(const T &elem) {
    std::shared_ptr<Node> newNode = std::make_shared<Node>(elem);
    bool nodeAdded = false;

    if (!root) {
        root = newNode;
        nodeAdded = true;
    } else {
        std::shared_ptr<Node> current = root;

        while (true) {
            T const &currElem = **current;

            if (elem == currElem) {
                // element being inserted is a duplicate.
                // increment node's counter.
                ++(*current);
                break;
            } else {
                // continue traversing tree to find insertion point.
                if (elem < currElem) {
                    if (current->hasLeft()) {
                        current = current->left;
                    } else {
                        current->left = newNode;
                        newNode->parent = current;
                        nodeAdded = true;
                        break; // we're done.  break out of loop
                    }
                } else if (elem > currElem) {
                    if (current->hasRight()) {
                        current = current->right;
                    } else {
                        current->right = newNode;
                        newNode->parent = current;
                        nodeAdded = true;
                        break; // we're done.  break out of loop
                    }
                }
            }
        }
    }

    // only perform an update if a new node was added.
    if (nodeAdded) {
        n++;
        update(newNode);
    }
}

template<typename T>
void CountingRedBlackTree<T>::update(std::shared_ptr<Node> &p) {
    std::shared_ptr<Node> u;

    if (root == p) {
        p->color = BLACK;
        return;
    }

    while (p->parent != nullptr && p->parent->color == RED) {
        auto g = p->parent->parent;

        if (g->left == p->parent) {
            if (g->hasRight()) {
                u = g->right;

                if (u->color == RED) {
                    p->parent->color = BLACK;
                    u->color = BLACK;
                    g->color = RED;
                    p = g;
                } else {
                    break; // nothing to do. break out of loop.
                }
            } else {
                if (p->parent->right == p) {
                    p = p->parent;
                    rotateLeft(p);
                }

                p->parent->color = BLACK;
                g->color = RED;

                rotateRight(g);
            }
        } else {
            if (g->hasLeft()) {
                u = g->left;

                if (u->color == RED) {
                    p->parent->color = BLACK;
                    u->color = BLACK;
                    g->color = RED;
                    p = g;
                } else {
                    break; // nothing to do. break out of loop.
                }
            } else {
                if (p->parent->left == p) {
                    p = p->parent;

                    rotateRight(p);
                }

                p->parent->color = BLACK;
                g->color = RED;

                rotateLeft(g);
            }
        }

        // ensure root is always BLACK and its parent is NULL.
        root->color = BLACK;
        root->parent = nullptr;
    }
}

template<typename T>
void CountingRedBlackTree<T>::rotateLeft(std::shared_ptr<Node> &p) {
    if (!p->hasRight()) {
        return;
    }

    std::shared_ptr<Node> y = p->right;

    if (y->hasLeft()) {
        p->right = y->left;
        y->left->parent = p;
    } else {
        p->right = nullptr;
    }

    if (p->parent != nullptr) {
        y->parent = p->parent;
    }

    if (p->parent == nullptr) {
        root = y;
    } else {
        if (p == p->parent->left) {
            p->parent->left = y;
        } else {
            p->parent->right = y;
        }
    }

    y->left = p;
    p->parent = y;
}

template<typename T>
void CountingRedBlackTree<T>::rotateRight(std::shared_ptr<Node> &p) {
    if (p->left == nullptr) {
        return;;
    }

    std::shared_ptr<Node> y = p->left;

    if (y->hasRight()) {
        p->left = y->right;
        y->right->parent = p;
    } else {
        p->left = nullptr;
    }

    if (p->parent != nullptr) {
        y->parent = p->parent;
    }

    if (p->parent == nullptr) {
        root = y;
    } else {
        if (p == p->parent->left) {
            p->parent->left = y;
        } else {
            p->parent->right = y;
        }
    }

    y->right = p;
    p->parent = y;
}

template<typename T>
void CountingRedBlackTree<T>::inOrder(std::shared_ptr<Node> p, typename Position::PositionList &pl) const {
    if (p == nullptr) {
        return;
    }

    inOrder(p->left, pl);
    pl.push_back(Position(p));
    inOrder(p->right, pl);
}


template<typename T>
typename CountingRedBlackTree<T>::Position::PositionList CountingRedBlackTree<T>::getPositions() const {
    std::list<Position> pl = Position::PositionList();
    inOrder(root, pl);

    return pl;
}
