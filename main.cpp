#include "AVL.h"
#include <iostream>

using namespace std;

int main()
{
    AVL tree;
    tree.insert("PEREZ", 15);
    tree.insert("DANIEL", 5);
    tree.insert("AND", 300);
    tree.insert("I", 1);
    tree.insert("AM", 3);
    tree.insert("TODAY", 301);
    tree.insert("IS", 303);
    tree.insert("DANIEL", 11);
    // tree.insert("PEREZ", 12);
    // tree.insert("AND", 888);
    // tree.insert("SUNDAY", 888);
    // tree.remove(3);

    // cout << "data:" << tree.find(15)->data << endl;

    cout << "\n inoreder:" << endl;
    tree.inorder();

    if (tree.isBalanced())
        cout << "BALANCED" << endl;
    else
        cout << "NOT BALANCED" << endl;
}