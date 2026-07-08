#include <iostream>
#include <string>
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

    // FIX: dung phep so sanh (==) thay vi phep gan (=)
    // Loi cu "return root = NULL;" se XOA mat goc cay moi khi goi ham nay!
    bool isEmpty()
    {
        return root == NULL;
    }
    bool isInternal(TreeNode<T> *v)
    {
        return (v->hasChild());
    }
    bool isExternal(TreeNode<T> *v)
    {
        return (!v->hasChild());
    }
    // FIX: dung phep so sanh (==) thay vi phep gan (=)
    // Loi cu "return v->getParent() = NULL;" se lam MAT lien ket cha cua node!
    bool isRoot(TreeNode<T> *v)
    {
        return v->getParent() == NULL;
    }

    // FIX: tham so phai la TreeNode<T>* (kieu cua cay hien tai)
    // Ban goc ghi cung la TreeNode<int>*, nen Tree<string> (dung cho Bai 2, Bai 3) se khong dich duoc.
    void preOrder(TreeNode<T> *root, string p = "\n")
    {
        if (root == 0)
            return;
        cout << p << root->getElem();
        for (auto z : root->getChild())
            preOrder(z, p + "\t");
    }

    void inOrder(TreeNode<T> *root, string p = "\n")
    {
        if (root == 0)
            return;
        if (root->hasChild())
            inOrder(root->getChild()[0], p + "\t");
        cout << p << root->getElem();
        for (size_t i = 1; i < root->getChild().size(); ++i)
            inOrder(root->getChild()[i], p + "\t");
    }

    void postOrder(TreeNode<T> *root, string p = "\n")
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
            parent->insertChild(newChild);
        ++n;
        return newChild;
    }

    // FIX: chuyen remove() thanh ham thanh vien dung kieu T (truoc kia la ham
    // rieng ben ngoai, chi nhan TreeNode<int>* nen khong dung duoc cho cay string),
    // va kiem tra v != NULL TRUOC khi goi v->hasChild() de tranh loi truy cap null.
    void remove(TreeNode<T> *v)
    {
        if (v == NULL)
            return;
        for (auto z : v->getChild())
            remove(z);
        v->getChild().clear();

        TreeNode<T> *parent = v->getParent();
        if (parent != NULL)
        {
            auto &siblings = parent->getChild();
            for (auto it = siblings.begin(); it != siblings.end(); ++it)
            {
                if (*it == v)
                {
                    siblings.erase(it);
                    break;
                }
            }
        }
        else
        {
            root = NULL;
        }
        delete v;
        --n;
    }
};

// ===================== Bai 1: demo cau truc cay co ban =====================
void bai1()
{
    cout << "=== Bai 1: Demo cau truc cay (Tree/TreeNode) ===";
    Tree<int> tree;
    tree.insert(NULL, 1);
    TreeNode<int> *p = tree.insert(tree.getRoot(), 2);
    TreeNode<int> *q = tree.insert(tree.getRoot(), 3);
    tree.insert(p, 4);
    tree.insert(p, 5);
    tree.insert(q, 6);

    cout << "\nPreOrder:";
    tree.preOrder(tree.getRoot());
    cout << "\n\nInOrder:";
    tree.inOrder(tree.getRoot());
    cout << "\n\nPostOrder:";
    tree.postOrder(tree.getRoot());
    cout << "\n";
}

// ============ Bai 2: cay bieu thuc (((a+b)-c)*((45-a)/(x-y)))/(a-x) =========
void bai2()
{
    cout << "\n=== Bai 2: Cay bieu thuc (((a+b)-c)*((45-a)/(x-y)))/(a-x) ===";
    Tree<string> tree;

    TreeNode<string> *root = tree.insert(NULL, "/");        // goc

    TreeNode<string> *mul = tree.insert(root, "*");         // ((a+b)-c)*((45-a)/(x-y))
    TreeNode<string> *subAX = tree.insert(root, "-");       // (a-x)
    tree.insert(subAX, "a");
    tree.insert(subAX, "x");

    TreeNode<string> *subABC = tree.insert(mul, "-");       // (a+b)-c
    TreeNode<string> *addAB = tree.insert(subABC, "+");     // a+b
    tree.insert(addAB, "a");
    tree.insert(addAB, "b");
    tree.insert(subABC, "c");

    TreeNode<string> *div2 = tree.insert(mul, "/");         // (45-a)/(x-y)
    TreeNode<string> *sub45A = tree.insert(div2, "-");      // 45-a
    tree.insert(sub45A, "45");
    tree.insert(sub45A, "a");
    TreeNode<string> *subXY = tree.insert(div2, "-");       // x-y
    tree.insert(subXY, "x");
    tree.insert(subXY, "y");

    cout << "\nPreOrder:";
    tree.preOrder(tree.getRoot());
    cout << "\n\nInOrder:";
    tree.inOrder(tree.getRoot());
    cout << "\n\nPostOrder:";
    tree.postOrder(tree.getRoot());
    cout << "\n";
}

// ===================== Bai 3: cay theo mo ta de bai ========================
void bai3()
{
    cout << "\n=== Bai 3: Cay theo mo ta (goc X) ===";
    Tree<string> tree;

    TreeNode<string> *X = tree.insert(NULL, "X");
    TreeNode<string> *A = tree.insert(X, "A");
    TreeNode<string> *B = tree.insert(X, "B");
    tree.insert(X, "C");
    TreeNode<string> *D = tree.insert(X, "D");

    tree.insert(A, "A1");
    tree.insert(A, "A2");

    tree.insert(B, "M");
    tree.insert(B, "N");
    TreeNode<string> *K = tree.insert(B, "K");
    tree.insert(K, "K1");
    tree.insert(K, "K2");

    tree.insert(D, "D1");
    tree.insert(D, "D2");
    TreeNode<string> *D3 = tree.insert(D, "D3");
    tree.insert(D3, "Z");
    tree.insert(D3, "Y");

    cout << "\nPreOrder:";
    tree.preOrder(tree.getRoot());
    cout << "\n";
}

int main()
{
    bai1();
    bai2();
    bai3();
    return 0;
}