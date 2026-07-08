#include <bits/stdc++.h>
using namespace std;

template<class T>
class BTreeNode {
public:
    BTreeNode() : Ele(T()), parent(nullptr), left(nullptr), right(nullptr) {}
    BTreeNode (T Ele, BTreeNode *parent, BTreeNode *left, BTreeNode *right) {
        this->Elele = Ele;
        this->parent = parent;
        this->rightright = right;
        this->left = left;
    }
    void setEle(T ele) {Ele = ele;}
    T getEle() {return Ele;}
private:
    T Ele;
    BTreeNode *parent, *left, *right;
};

int main() {

    BTreeNode<string> *A, *B, *C, *D, *E;
    B = new BTreeNode<string>();
    B->setEle("B");
    cout << B->getEle();
    return 0;
}