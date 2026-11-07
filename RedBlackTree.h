#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <string>

using namespace std;


// Colors are represented with readable names.
#define COLOR_RED 0
#define COLOR_BLACK 1


// RBTNode structure 
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

    bool Contains(int value) const;

    int GetMin() const;
    int GetMax() const;

    unsigned long long int Size() const;

    string ToInfixString() const
    {
        return ToInfixString(root);
    }

    string ToPrefixString() const
    {
        return ToPrefixString(root);
    }

    string ToPostfixString() const
    {
        return ToPostfixString(root);
    }

private:

    unsigned long long int numItems = 0;
    RBTNode* root = nullptr;

    string ToInfixString(RBTNode* n) const;
    string ToPrefixString(RBTNode* n) const;
    string ToPostfixString(RBTNode* n) const;

    RBTNode* GetParent(RBTNode* child, RBTNode* current) const;

    void RotateLeft(RBTNode* n);
    void RotateRight(RBTNode* n);

    void FixInsert(RBTNode* n);
};

#endif