#ifndef AVL_H
#define AVL_H

#include "Node.h"
#include <memory>
#include <iostream>
#include <iomanip>

enum struct StatusType
{
    SUCCESS = 0,
    ALLOCATION_ERROR = 1,
    INVALID_INPUT = 2,
    FAILURE = 3,
};

class AVL
{
private:
    Node *root;
    void rr_rotation(Node *v);
    void ll_rotation(Node *v);
    void rl_rotation(Node *v);
    void lr_rotation(Node *v);
    void destructRecursive(Node *node);
    void recursiveInorder(Node *node);
    void recursivePostorder(Node *node);
    void recursivePreorder(Node *node);
    bool balanceNodeParent(Node *node);
    void swapNodesLocation(Node *a, Node *b);

public:
    AVL() : root(nullptr){};
    ~AVL();
    StatusType insert(std::string data, int key);
    StatusType remove(int key);
    void inorder();
    void postorder();
    void preorder();

    void balanceTreeAfterInsert(Node *node);
    void balanceTreeAfterRemoval(Node *node);

    Node *find(int key);

    // TODO: test funcitons:
    bool isBalanced()
    {
        bool isBalanced = true;
        recursiveIsBalnced(root, isBalanced);
        return isBalanced;
    }

    void recursiveIsBalnced(Node *node, bool &isBalanced)
    {
        if (node == NULL)
            return;

        recursiveIsBalnced(node->left, isBalanced);
        recursiveIsBalnced(node->right, isBalanced);
        if (node->bf() < -1 || node->bf() > 1)
        {
            isBalanced = false;
            std::cout << "NODE KEY: " << node->key << " NODE BF: " << node->bf() << std::endl;
            if (node->left)
                std::cout << "left: " << node->left->key << std::endl;
            if (node->right)
                std::cout << "RIGHT: " << node->right->key << std::endl;
            if (node->parent)
                std::cout << "PARENT: " << node->parent->key << std::endl;
        }
    }
};

#endif // AVL_H