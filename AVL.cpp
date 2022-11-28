#include "AVL.h"
#include "iostream"

using namespace std;

AVL::~AVL()
{
    destructRecursive(root);
}

void AVL::destructRecursive(Node *node)
{
    if (node)
    {
        destructRecursive(node->right);
        destructRecursive(node->left);
        delete node;
    }
}

void AVL::ll_rotation(Node *v)
{
    cout << "performing ll on: " << v->key << endl;
    Node *newTop = v->left;
    Node *temp = newTop->right;

    newTop->right = v;
    v->left = temp;

    if (temp)
        temp->parent = v;
    newTop->parent = v->parent;
    if (v->parent == nullptr)
        root = newTop;
    else if (v->parent->left == v) // v is left child
        v->parent->left = newTop;
    else // v is right child
        v->parent->right = newTop;
    v->parent = newTop;

    v->height = max(v->getLeftHeight(), v->getLeftHeight()) + 1;
    newTop->height = max(v->getLeftHeight(), v->getLeftHeight()) + 1;
}

void AVL::rr_rotation(Node *v)
{
    cout << "performing rr on: " << v->key << endl;
    Node *newTop = v->right;
    Node *temp = newTop->left;

    newTop->left = v;
    v->right = temp;

    if (temp)
        temp->parent = v;

    newTop->parent = v->parent;
    if (v->parent == nullptr)
        root = newTop;
    else if (v->parent->left == v) // v is left child
        v->parent->left = newTop;
    else // v is right child
        v->parent->right = newTop;
    v->parent = newTop;

    v->height = max(v->getLeftHeight(), v->getLeftHeight()) + 1;
    newTop->height = max(v->getLeftHeight(), v->getLeftHeight()) + 1;
}
void AVL::rl_rotation(Node *v)
{
    cout << "performing rl on: " << v->key << endl;
    ll_rotation(v->right);
    rr_rotation(v);
}
void AVL::lr_rotation(Node *v)
{
    cout << "performing lr on: " << v->key << endl;
    rr_rotation(v->left);
    ll_rotation(v);
}

void AVL::inorder()
{
    recursiveInorder(root);
}

void AVL::postorder()
{
    recursivePostorder(root);
}

void AVL::preorder()
{
    recursivePreorder(root);
}

void AVL::recursiveInorder(Node *node)
{
    if (node == nullptr)
        return;
    recursiveInorder(node->left);
    cout << node->data << endl;
    // cout << "node-bf: " << node->bf() << endl;
    // cout << "node-height: " << node->height << endl;
    recursiveInorder(node->right);
}

void AVL::recursivePostorder(Node *node)
{
    if (node == nullptr)
        return;
    recursivePostorder(node->left);
    recursivePostorder(node->right);
    cout << node->data << endl;
}

void AVL::recursivePreorder(Node *node)
{
    if (node == nullptr)
        return;
    cout << node->data << endl;
    recursivePreorder(node->left);
    recursivePreorder(node->right);
}

StatusType AVL::insert(std::string data, int key)
{
    if (root == nullptr)
    {
        root = new Node(key, data);
        cout << "inserted: " << key << " as root" << endl;
        return StatusType::SUCCESS;
    }
    if (find(key))
    {
        cout << "key already exists" << endl;
        return StatusType::FAILURE;
    }
    Node *v = root;
    while (true)
    {
        if (key < v->key)
        {
            if (v->left == nullptr)
            {
                v->left = new Node(key, data);
                v->left->parent = v;
                cout << "inserted: " << key << " as left child of: " << v->key << endl;
                balanceTreeAfterInsert(v->left);
                return StatusType::SUCCESS;
            }
            v = v->left;
        }
        else // key > v.key
        {
            if (v->right == nullptr)
            {
                v->right = new Node(key, data);
                v->right->parent = v;
                cout << "inserted: " << key << " as right child of: " << v->key << endl;
                balanceTreeAfterInsert(v->right);
                return StatusType::SUCCESS;
            }
            v = v->right;
        }
    }
}

bool AVL::balanceNodeParent(Node *node)
{

    int parentBf = (*(node->parent)).bf();
    int nodeBf = (*(node)).bf();
    if ((parentBf == 2) && (node == node->parent->left) && (nodeBf > -1))
    {
        ll_rotation(node->parent);
        return true;
    }
    if ((parentBf == -2) && (node == node->parent->right) && (nodeBf < 1))
    {
        rr_rotation(node->parent);
        return true;
    }
    if ((parentBf == 2) && (node == node->parent->left) && (nodeBf == -1))
    {
        lr_rotation(node->parent);
        return true;
    }
    if ((parentBf == -2) && (node == node->parent->right) && (nodeBf == 1))
    {
        rl_rotation(node->parent);
        return true;
    }
    return false;
}

void AVL::balanceTreeAfterInsert(Node *node)
{
    while (node != root)
    {
        if (node->parent->height >= node->height + 1)
            return;
        node->parent->height = node->height + 1;
        if (balanceNodeParent(node))
            return;
        node = node->parent;
    }
}

void AVL::balanceTreeAfterRemoval(Node *node)
{
    while (node != root)
    {
        if (node->parent->height >= node->height + 1)
            return;
        node->parent->height = node->height + 1;
        balanceNodeParent(node);
        node = node->parent;
    }
}

StatusType AVL::remove(int key)
{
    Node *nodeToRemove = find(key);
    if (!nodeToRemove)
        return StatusType::FAILURE;
    if (nodeToRemove->left && nodeToRemove->right)
    {
        Node *followingNode = nodeToRemove->right;
        while (followingNode->left)
        {
            followingNode = followingNode->left;
        }
        swapNodesLocation(nodeToRemove, followingNode);
        nodeToRemove = followingNode; // now node to remove is wither a leaf or has single child
    }
    // case node is a leaf has single child:
    Node *son = nodeToRemove->left ? nodeToRemove->left : nodeToRemove->right; // hold the son or nullptr
    if (son)
        son->parent = nodeToRemove->parent;
    if (nodeToRemove == root) // case nodeToRemove is root
    {
        root = son;
        delete nodeToRemove;
        return StatusType::SUCCESS;
    }
    if (nodeToRemove == nodeToRemove->parent->left) // case node to remove is left son
        nodeToRemove->parent->left = son;
    else // nodeToRemove is a right son
        nodeToRemove->parent->right = son;
    delete nodeToRemove;
    return StatusType::SUCCESS;
}

Node *AVL::find(int key)
{
    Node *v = root;
    while (v)
    {
        if (key == v->key)
            return v;
        if (key < v->key)
            v = v->left;
        else // key > v-> key
            v = v->right;
    }
    return v;
}

void AVL::swapNodesLocation(Node *a, Node *b)
{
    string aData = a->data;
    int aKey = a->key;

    a->data = b->data;
    a->key = b->key;

    b->data = aData;
    b->key = aKey;
}