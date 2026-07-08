#include <bits/stdc++.h>
using namespace std;

template <class Keys, class T>
class Node
{
private:
    Keys key;
    T elem;
    Node *parent;
    Node *left;
    Node *right;

public:
    Node() : elem(), key(), parent(nullptr), left(nullptr), right(nullptr) {}
    Node(Keys k, T e) : elem(e), key(k), parent(nullptr), left(nullptr), right(nullptr) {}
    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;
    ~Node()
    {
        if (left != nullptr)
        {
            delete left;
        }
        if (right != nullptr)
        {
            delete right;
        }
    }
    Node *getParent() { return parent; }
    Node *getLeft() { return left; }
    Node *getRight() { return right; }
    void setLeft(Node *l) { left = l; }
    void setRight(Node *r) { right = r; }
    void setParent(Node *p) { parent = p; }
    int hasLeft() { return left != nullptr ? 1 : 0; } // sửa: 1/0 thay vì 1/-1
    int hasRight() { return right != nullptr ? 1 : 0; }
    T getElem() { return elem; }
    void setElem(T e) { elem = e; }
    Keys getKey() { return key; }
    void setKey(Keys k) { key = k; }
};

template <class Keys, class T>
class BST
{
private:
    Node<Keys, T> *root;
    int n;

public:
    BST() : root(nullptr), n(0) {}
    ~BST()
    {
        delete root;
    }
    BST(const BST &) = delete; // cấm copy constructor
    BST &operator=(const BST &) = delete;
    Node<Keys, T> *getRoot() { return root; }
    int size() { return n; }
    int countNode(Node<Keys, T> *p)
    {
        if (p == nullptr)
            return 0;
        int cnt = 1;
        if (p->hasLeft())
            cnt += countNode(p->getLeft()); // if, không phải while
        if (p->hasRight())
            cnt += countNode(p->getRight());
        return cnt;
    }

    int isEmpty() { return n == 0 ? 1 : -1; }
    int isInternal(Node<Keys, T> *a) { return (a->hasLeft() || a->hasRight()) ? 1 : -1; }
    int isExternal(Node<Keys, T> *a) { return (!a->hasLeft() && !a->hasRight()) ? 1 : -1; }
    int isRoot(Node<Keys, T> *a) { return (a->getParent() == nullptr) ? 1 : -1; }
    void preOrder(Node<Keys, T> *p, void (*visit)(Node<Keys, T> *))
    {
        if (p == nullptr)
            return;
        visit(p);
        if (p->hasLeft())
            preOrder(p->getLeft(), visit);
        if (p->hasRight())
            preOrder(p->getRight(), visit);
    }
    void inOrder(Node<Keys, T> *p, void (*visit)(Node<Keys, T> *))
    {
        if (p == nullptr)
            return;
        if (p->hasLeft())
            inOrder(p->getLeft(), visit);
        visit(p);
        if (p->hasRight())
            inOrder(p->getRight(), visit);
    }
    void postOrder(Node<Keys, T> *p, void (*visit)(Node<Keys, T> *))
    {
        if (p == nullptr)
            return;
        if (p->hasLeft())
            postOrder(p->getLeft(), visit);
        if (p->hasRight())
            postOrder(p->getRight(), visit);
        visit(p);
    }
    void insert(Keys k, T val)
    {
        Node<Keys, T> *newNode = new Node<Keys, T>(k, val);
        if (root == nullptr)
        {
            root = newNode;
            ++n;
            return;
        }
        Node<Keys, T> *cur = root;
        while (cur != nullptr)
        {
            if (k < cur->getKey())
            {
                if (cur->getLeft() == nullptr)
                {
                    cur->setLeft(newNode);
                    newNode->setParent(cur);
                    ++n;
                    return;
                }
                cur = cur->getLeft();
            }
            else
            {
                if (cur->getRight() == nullptr)
                {
                    cur->setRight(newNode);
                    newNode->setParent(cur);
                    ++n;
                    return;
                }
                cur = cur->getRight();
            }
        }
    }
    Node<Keys, T> *search(Keys k)
    {
        Node<Keys, T> *cur = root;
        while (cur != nullptr)
        {
            if (cur->getKey() == k)
                return cur;
            cur = (k < cur->getKey()) ? cur->getLeft() : cur->getRight();
        }
        return nullptr;
    }
    void remove(Keys k)
    {
        Node<Keys, T> *p = search(k);
        if (p == nullptr)
            return;

        // TH1: lá
        if (p->getLeft() == nullptr && p->getRight() == nullptr)
        {
            if (p == root)
                root = nullptr;
            else
            {
                Node<Keys, T> *par = p->getParent();
                if (par->getLeft() == p)
                    par->setLeft(nullptr);
                else
                    par->setRight(nullptr);
            }
            delete p;
            --n;
            return;
        }

        // TH2: có con trái → rightmost của cây con trái
        if (p->getLeft() != nullptr)
        {
            Node<Keys, T> *rightest = p->getLeft();
            while (rightest->getRight() != nullptr)
                rightest = rightest->getRight();

            p->setKey(rightest->getKey());
            p->setElem(rightest->getElem());

            Node<Keys, T> *par = rightest->getParent();
            Node<Keys, T> *leftChild = rightest->getLeft(); // rightest chỉ có thể có con trái

            if (par == p)
                par->setLeft(leftChild);
            else
                par->setRight(leftChild);

            if (leftChild != nullptr)
                leftChild->setParent(par);

            rightest->setLeft(nullptr);
            delete rightest;
            --n;
            return;
        }

        // TH3: chỉ có con phải → leftmost của cây con phải
        {
            Node<Keys, T> *leftest = p->getRight();
            while (leftest->getLeft() != nullptr)
                leftest = leftest->getLeft();

            p->setKey(leftest->getKey());
            p->setElem(leftest->getElem());

            Node<Keys, T> *par = leftest->getParent();
            Node<Keys, T> *rightChild = leftest->getRight(); // leftest chỉ có thể có con phải

            if (par == p)
                par->setRight(rightChild);
            else
                par->setLeft(rightChild);

            if (rightChild != nullptr)
                rightChild->setParent(par);

            leftest->setRight(nullptr);
            delete leftest;
            --n;
        }
    }
};

template <class Keys, class T>
void printNode(Node<Keys, T> *p)
{
    cout << p->getElem() << " ";
}

int main()
{
    BST<int, int> tree;

    // ── Insert ────────────────────────────────
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(8, 80);
    tree.insert(1, 10);
    tree.insert(4, 40);
    tree.insert(6, 60);
    tree.insert(9, 90);

    cout << "size     : " << tree.size()    << "\n";  // 7
    cout << "isEmpty  : " << tree.isEmpty() << "\n";  // -1

    // ── Duyệt ─────────────────────────────────
    // inOrder BST luôn ra thứ tự tăng dần theo key
    cout << "\ninOrder  : "; tree.inOrder(tree.getRoot(), printNode<int,int>);
    // 10 30 40 50 60 80 90  (val theo key tăng dần)

    cout << "\npreOrder : "; tree.preOrder(tree.getRoot(), printNode<int,int>);
    // 50 30 10 40 80 60 90

    cout << "\npostOrder: "; tree.postOrder(tree.getRoot(), printNode<int,int>);
    // 10 40 30 60 90 80 50

    // ── Search ────────────────────────────────
    cout << "\n\nsearch(3): ";
    Node<int,int>* res = tree.search(3);
    cout << (res ? to_string(res->getElem()) : "null") << "\n";  // 30

    cout << "search(7): ";
    res = tree.search(7);
    cout << (res ? to_string(res->getElem()) : "null") << "\n";  // null

    // ── Remove TH1: xóa lá (key=1) ───────────
    cout << "\n--- remove(1): xóa lá ---\n";
    tree.remove(1);
    cout << "size     : " << tree.size() << "\n";  // 6
    cout << "inOrder  : "; tree.inOrder(tree.getRoot(), printNode<int,int>);
    // 30 40 50 60 80 90

    // ── Remove TH3: xóa node chỉ có con phải (key=3, còn lại con phải là 4) ──
    cout << "\n\n--- remove(3): chỉ có con phải ---\n";
    tree.remove(3);
    cout << "size     : " << tree.size() << "\n";  // 5
    cout << "inOrder  : "; tree.inOrder(tree.getRoot(), printNode<int,int>);
    // 40 50 60 80 90

    // ── Remove TH2: xóa node có 2 con (key=8) ─
    cout << "\n\n--- remove(8): có 2 con ---\n";
    tree.remove(8);
    cout << "size     : " << tree.size() << "\n";  // 4
    cout << "inOrder  : "; tree.inOrder(tree.getRoot(), printNode<int,int>);
    // 40 50 60 90

    // ── Remove root ───────────────────────────
    cout << "\n\n--- remove(5): xóa root ---\n";
    tree.remove(5);
    cout << "size     : " << tree.size() << "\n";  // 3
    cout << "inOrder  : "; tree.inOrder(tree.getRoot(), printNode<int,int>);
    // 40 60 90
    cout << "\n";

    return 0;
}