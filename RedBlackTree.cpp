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
    // First node becomes the black root.
    if(root == nullptr)
    {
        root = new RBTNode;

        root->data = value;
        root->color = COLOR_BLACK;

        numItems++;

        return;
    }

    RBTNode* current = root;

    while(true)
    {
        if(value == current->data)
        {
            throw invalid_argument("Duplicate value.");
        }

        if(value < current->data)
        {
            if(current->left == nullptr)
            {
                current->left = new RBTNode;

                current->left->data = value;
                current->left->color = COLOR_RED;

                numItems++;

                return;
            }

            current = current->left;
        }

        else
        {
            if(current->right == nullptr)
            {
                current->right = new RBTNode;

                current->right->data = value;
                current->right->color = COLOR_RED;

                numItems++;

                return;
            }

            current = current->right;
        }
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

string RedBlackTree::ToPrefixString(RBTNode* n) const
{
    if(n == nullptr)
    {
        return "";
    }

    string result = "";

    if(n->color == COLOR_BLACK)
    {
        result += " B" + to_string(n->data) + " ";
    }
    else
    {
        result += " R" + to_string(n->data) + " ";
    }

    result += ToPrefixString(n->left);
    result += ToPrefixString(n->right);

    return result;
}

string RedBlackTree::ToPostfixString(RBTNode* n) const
{
    if(n == nullptr)
    {
        return "";
    }

    string result = "";

    result += ToPostfixString(n->left);
    result += ToPostfixString(n->right);

    if(n->color == COLOR_BLACK)
    {
        result += " B" + to_string(n->data) + " ";
    }
    else
    {
        result += " R" + to_string(n->data) + " ";
    }

    return result;
}

