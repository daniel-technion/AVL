#ifndef NODE_H
#define NODE_H

#include <memory>
#include <string>

class Node
{
public:
    Node(int key, std::string data) : key(key), data(data), left(nullptr), right(nullptr), parent(nullptr), height(0){};
    ~Node() = default;
    int key;
    std::string data;
    Node *left;
    Node *right;
    Node *parent;
    int height;

    int bf();
    int getRightHeight();
    int getLeftHeight();
};

#endif // NODE_H