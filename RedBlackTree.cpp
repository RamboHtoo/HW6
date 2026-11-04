#include "RedBlackTree.h"

using namespace std;


// I used ChatGPT to discuss red-black tree structure,
// traversal, insertion, and testing.


RedBlackTree::RedBlackTree()
{
    root = nullptr;
    numItems = 0;
}

RedBlackTree::RedBlackTree(int value)
{
    root = nullptr;
    numItems = 0;

    Insert(value);
}

void RedBlackTree::Insert(int value)
{
    // First node inserted into an empty tree becomes the root.
    if(root == nullptr)
    {
        root = new RBTNode;

        root->data = value;
        root->color = COLOR_BLACK;

        root->left = nullptr;
        root->right = nullptr;

        numItems++;

        return;
    }
}

string RedBlackTree::ToInfixString(RBTNode* n) const
{
    if(n == nullptr)
    {
        return "";
    }

    string result = "";

    result += ToInfixString(n->left);

    if(n->color == COLOR_BLACK)
    {
        result += " B" + to_string(n->data) + " ";
    }
    else
    {
        result += " R" + to_string(n->data) + " ";
    }

    result += ToInfixString(n->right);

    return result;
}