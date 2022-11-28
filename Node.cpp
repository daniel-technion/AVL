#include "Node.h"
#include <iostream>

int Node::bf()
{
    return getLeftHeight() - getRightHeight();
}

int Node::getRightHeight()
{
    return right == nullptr ? -1 : right->height;
}

int Node::getLeftHeight()
{
    return left == nullptr ? -1 : left->height;
}
