#include "RedBlackTree.h"
#include <stdexcept>

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
                RBTNode* newNode = new RBTNode;

                newNode->data = value;
                newNode->color = COLOR_RED;

                current->left = newNode;

                numItems++;

                FixInsert(newNode);

                return;
            }

            current = current->left;
        }

        else
        {
            if(current->right == nullptr)
            {
                RBTNode* newNode = new RBTNode;

                newNode->data = value;
                newNode->color = COLOR_RED;

                current->right = newNode;

                numItems++;

                FixInsert(newNode);

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


bool RedBlackTree::Contains(int value) const
{
    RBTNode* current = root;

    while(current != nullptr)
    {
        if(value == current->data)
        {
            return true;
        }

        if(value < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return false;
}

unsigned long long int RedBlackTree::Size() const
{
    return numItems;
}

RBTNode* RedBlackTree::GetParent(
    RBTNode* child,
    RBTNode* current) const
{
    // The root has no parent.
    if(child == root || current == nullptr)
    {
        return nullptr;
    }

    // Check whether current directly owns child.
    if(current->left == child ||
       current->right == child)
    {
        return current;
    }

    // Use BST ordering to continue down only one side.
    if(child->data < current->data)
    {
        return GetParent(child, current->left);
    }

    return GetParent(child, current->right);
}

void RedBlackTree::RotateLeft(RBTNode* n)
{
    /*
     * Before:
     *
     *       n
     *        \
     *         newTop
     *         /
     *      middle
     *
     * After:
     *
     *        newTop
     *        /
     *       n
     *        \
     *       middle
     */

    RBTNode* oldParent = GetParent(n, root);

    RBTNode* newTop = n->right;

    // Move the middle subtree.
    n->right = newTop->left;

    // Put n underneath newTop.
    newTop->left = n;


    // Reconnect this rotated subtree to the rest of the tree.
    if(oldParent == nullptr)
    {
        root = newTop;
    }
    else if(oldParent->left == n)
    {
        oldParent->left = newTop;
    }
    else
    {
        oldParent->right = newTop;
    }
}

void RedBlackTree::RotateRight(RBTNode* n)
{
    /*
     * Before:
     *
     *         n
     *        /
     *    newTop
     *       \
     *      middle
     *
     * After:
     *
     *      newTop
     *          \
     *           n
     *          /
     *       middle
     */

    RBTNode* oldParent = GetParent(n, root);

    RBTNode* newTop = n->left;

    // Move the middle subtree.
    n->left = newTop->right;

    // Put n underneath newTop.
    newTop->right = n;


    // Reconnect the rotated subtree.
    if(oldParent == nullptr)
    {
        root = newTop;
    }
    else if(oldParent->left == n)
    {
        oldParent->left = newTop;
    }
    else
    {
        oldParent->right = newTop;
    }
}

void RedBlackTree::FixInsert(RBTNode* n)
{
    /*
     * A newly inserted node is red.
     *
     * We only have a problem when its parent is also red,
     * because a red node may not have a red child.
     */
    while(n != root)
    {
        RBTNode* parent = GetParent(n, root);

        // If the parent is black, the tree is already valid.
        if(parent == nullptr ||
           parent->color == COLOR_BLACK)
        {
            break;
        }


        RBTNode* grandparent =
            GetParent(parent, root);


        // Parent is on the LEFT side of grandparent.
        if(parent == grandparent->left)
        {
            RBTNode* uncle = grandparent->right;


            /*
             * Parent and uncle are both red:
             * recolor them black and move the red problem upward.
             */
            if(uncle != nullptr &&
               uncle->color == COLOR_RED)
            {
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;

                grandparent->color = COLOR_RED;

                n = grandparent;
            }

            else
            {
                /*
                 * LEFT-RIGHT case:
                 *
                 *       G
                 *      /
                 *     P
                 *      \
                 *       N
                 */
                if(n == parent->right)
                {
                    n = parent;
                    RotateLeft(n);

                    parent = GetParent(n, root);
                    grandparent =
                        GetParent(parent, root);
                }


                /*
                 * LEFT-LEFT case.
                 */
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;

                RotateRight(grandparent);
            }
        }


        // Parent is on the RIGHT side of grandparent.
        else
        {
            RBTNode* uncle = grandparent->left;


            if(uncle != nullptr &&
               uncle->color == COLOR_RED)
            {
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;

                grandparent->color = COLOR_RED;

                n = grandparent;
            }

            else
            {
                /*
                 * RIGHT-LEFT case.
                 */
                if(n == parent->left)
                {
                    n = parent;
                    RotateRight(n);

                    parent = GetParent(n, root);
                    grandparent =
                        GetParent(parent, root);
                }


                /*
                 * RIGHT-RIGHT case.
                 */
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;

                RotateLeft(grandparent);
            }
        }
    }


    // The root must always be black.
    root->color = COLOR_BLACK;
}

int RedBlackTree::GetMin() const
{
    if(root == nullptr)
    {
        throw invalid_argument("Tree is empty.");
    }

    RBTNode* current = root;

    // The smallest BST value is the farthest-left node.
    while(current->left != nullptr)
    {
        current = current->left;
    }

    return current->data;
}

int RedBlackTree::GetMax() const
{
    if(root == nullptr)
    {
        throw invalid_argument("Tree is empty.");
    }

    RBTNode* current = root;

    // The largest BST value is the farthest-right node.
    while(current->right != nullptr)
    {
        current = current->right;
    }

    return current->data;
}

RBTNode* RedBlackTree::CopyTree(RBTNode* n) const
{
    if(n == nullptr)
    {
        return nullptr;
    }

    RBTNode* copy = new RBTNode;

    copy->data = n->data;
    copy->color = n->color;

    copy->left = CopyTree(n->left);
    copy->right = CopyTree(n->right);

    return copy;
}

RedBlackTree::RedBlackTree(const RedBlackTree& other)
{
    numItems = other.numItems;

    root = CopyTree(other.root);
}

void RedBlackTree::DeleteTree(RBTNode* n)
{
    if(n == nullptr)
    {
        return;
    }

    DeleteTree(n->left);
    DeleteTree(n->right);

    delete n;
}

RedBlackTree::~RedBlackTree()
{
    DeleteTree(root);

    root = nullptr;
    numItems = 0;
}