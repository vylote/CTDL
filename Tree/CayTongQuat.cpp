#include <iostream>
#include "TreeNode.cpp"
using namespace std;

template <class T>
class Tree
{
    TreeNode<T> *root;
    int n;

public:
    Tree() : root(nullptr), n(0) {}
    TreeNode<T> *&getRoot() { return root; }
    int size() { return n; }
    int isEmpty()
    {
        return root = NULL;
    }
    int isInternal(TreeNode<T> *v)
    {
        return (v->hasChild());
    }
    int isExternal(TreeNode<T> *v)
    {
        return (!v->hasChild());
    }
    int isRoot(TreeNode<T> *v)
    {
        return v->getParent() = NULL;
    }
    void preOrder(TreeNode<int> *root, string p = "\n")
    {
        if (root == 0)
            return;
        cout << p << root->getElem();
        // co the dung vong lap for de duyet con nhung phai khoi tao chi so i
        for (auto z : root->getChild())
            preOrder(z, p + "\t");
    }

    void inOrder(TreeNode<int> *root, string p = "\n")
    {
        if (root == 0)
            return;
        if (root->hasChild())
        {
            inOrder(root->getChild()[0], p + "\t");
        }
        cout << p << root->getElem();
        /* for (size_t i = 0; i < root->getChild().size(); ++i) {
            inOrder(root->getChild(i), p+"\t");
        } */
        // day la cach duyet theo chi so
        for (int i = 1; i < root->getChild().size(); ++i)
            inOrder(root->getChild()[i], p + "\t");
    }
    void postOrder(TreeNode<int> *root, string p = "\n")
    {
        if (root == 0)
            return;
        for (auto z : root->getChild())
            postOrder(z, p + "\t");
        cout << p << root->getElem();
    }
    TreeNode<T> *insert(TreeNode<T> *parent, T element)
    {
        TreeNode<T> *newChild = new TreeNode<T>;
        newChild->setParent(parent);
        newChild->setElem(element);
        if (parent == NULL)
            root = newChild;
        else
        {
            parent->insertChild(newChild);
        }
        ++n;
        return newChild;
    }
};

void remove(TreeNode<int> *v)
{
    if (v != NULL)
    {
        for (auto z : v->getChild())
            remove(z);
    }
    if (v->hasChild())
        v->getChild().clear();
    TreeNode<int> *parent = v->getParent();
    if (parent != NULL)
    {
        for (auto z = parent->getChild().begin(); z != parent->getChild().end(); ++z)
        {
            if (*z == v)
            {
                parent->getChild().erase(z);
                break;
            }
        }
        delete v;
    }
}

int main()
{
    Tree<int> tree;
    tree.insert(NULL, 1);
    TreeNode<int> *p = tree.insert(tree.getRoot(), 2);
    TreeNode<int> *q = tree.insert(tree.getRoot(), 3);
    tree.insert(p, 4);
    tree.insert(p, 5);
    tree.insert(q, 6);
    tree.preOrder(tree.getRoot(), "\n");

    return 0;
}