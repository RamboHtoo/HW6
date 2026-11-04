#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <string>

using namespace std;


// Colors are represented with readable names.
#define COLOR_RED 0
#define COLOR_BLACK 1


// RBTNode structure from the lecture.
struct RBTNode
{
    int data;
    unsigned short int color;

    RBTNode* left = nullptr;
    RBTNode* right = nullptr;
};


class RedBlackTree
{
public:

    RedBlackTree();

    RedBlackTree(int value);

    void Insert(int value);

    string ToInfixString() const
    {
        return ToInfixString(root);
    }


private:

    unsigned long long int numItems = 0;

    RBTNode* root = nullptr;


    string ToInfixString(RBTNode* n) const;
};

#endif