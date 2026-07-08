#ifndef TreeNode_cpp
#define TreeNode_cpp
#include <iostream>
#include <vector>
using namespace std;

template <class Object>
class TreeNode
{
private:
    Object elem;
    TreeNode *parent;
    vector<TreeNode*> Child;

public:
    TreeNode(Object o = Object(), TreeNode *father = NULL) : elem(o), parent(father) {}
    TreeNode *&getParent() { return parent; }
    void setParent(TreeNode *father) { parent = father; }
    void insertChild(TreeNode *child) { Child.push_back(child); }
    vector<TreeNode *> &getChild() { return Child; }
    void setElem(Object o) { elem = o; }
    Object &getElem() { return elem; }
    bool hasChild() { return Child.size() > 0; }
    TreeNode*& getChild(int i) { return Child[i]; }
};
#endif