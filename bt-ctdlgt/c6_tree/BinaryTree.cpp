#include <bits/stdc++.h>
using namespace std;

template<class T>
class BTreeNode{    
    private:
        T elem;
        BTreeNode* parent;
        BTreeNode* left;
        BTreeNode* right;
    public:
        BTreeNode() : elem(), parent(nullptr), left(nullptr), right(nullptr) {}
        BTreeNode(T e) : elem(e), parent(nullptr), left(nullptr), right(nullptr) {}
        BTreeNode(const BTreeNode&)            = delete;
        BTreeNode& operator=(const BTreeNode&) = delete;
        ~BTreeNode() {
            if (left != nullptr) {
                delete left;
            }
            if (right != nullptr) {
                delete right;
            }
        }
        BTreeNode* getParent() {return parent;}
        BTreeNode* getLeft() {return left;}
        BTreeNode* getRight() {return right;}
        void setLeft(BTreeNode* l) {left = l;}
        void setRight(BTreeNode* r) {right=r;}
        void setParent(BTreeNode* p) {parent=p;}
        int hasLeft() {return left != nullptr ? 1 : 0;}   // sửa: 1/0 thay vì 1/-1
        int hasRight() {return right != nullptr ? 1 : 0;}
        T getElem() {return elem;}
        void setElem(T e) {elem = e;}
        bool insertNode(BTreeNode* a) {
            if(a == nullptr) return false;

            if(left == nullptr){
                left = a;
                a->parent = this;
                return true;
            }

            if(right == nullptr){
                right = a;
                a->parent = this;
                return true;
            }
            return false;
        }
};

template<class T>
class BTree{
    private:
        BTreeNode<T>* root;
        int n;
    public:
        BTree() : root(nullptr), n(0) {}
        ~BTree(){
            delete root;
        }
        BTree(const BTree&)            = delete;  // cấm copy constructor
        BTree& operator=(const BTree&) = delete; 
        BTreeNode<T>* getRoot() {return root;}
        int size() {return n;}
        int countNode(BTreeNode<T>* p) {
            if (p == nullptr) return 0;
            int cnt = 1;
            if (p->hasLeft())  cnt += countNode(p->getLeft());   // if, không phải while
            if (p->hasRight()) cnt += countNode(p->getRight());
            return cnt;
        }

        int isEmpty() {return n==0?1:-1;}
        int isInternal(BTreeNode<T>* a) {return (a->hasLeft() || a->hasRight())?1:-1;}
        int isExternal(BTreeNode<T>* a) {return (!a->hasLeft() && !a->hasRight()) ? 1 : -1;}
        int isRoot(BTreeNode<T>* a) {return (a->getParent()==nullptr)?1:-1;}
        void preOrder(BTreeNode<T>* p, void (*visit)(BTreeNode<T>*)) {
            if (p == nullptr) return;
            visit(p);
            if (p->hasLeft()) preOrder(p->getLeft(), visit);
            if (p->hasRight()) preOrder(p->getRight(), visit);
        }
        void inOrder(BTreeNode<T>* p, void (*visit)(BTreeNode<T>*)) {
            if (p == nullptr) return;
            if (p->hasLeft()) inOrder(p->getLeft(), visit);
            visit(p);
            if (p->hasRight()) inOrder(p->getRight(), visit);
        }
        void postOrder(BTreeNode<T>* p, void (*visit)(BTreeNode<T>*)) {
            if (p == nullptr) return;
            if (p->hasLeft()) postOrder(p->getLeft(), visit);
            if (p->hasRight()) postOrder(p->getRight(), visit);
            visit(p);
        }
        void insert(BTreeNode<T>* parent, T element) {
            BTreeNode<T>* newNode = new BTreeNode<T>(element); 
            if (parent == nullptr) {
                if (root == nullptr) {
                    root = newNode;
                    ++n;
                    return;
                }
                delete newNode;
                return;
            }
            if (!parent->insertNode(newNode)) { delete newNode; return; }
            ++n;
        }
        void remove(BTreeNode<T>* a) {
            if (a == nullptr) return;
            BTreeNode<T>* p = a->getParent();
            if (p != nullptr) {
                if (p->getLeft() == a) p->setLeft(nullptr);
                else if (p->getRight() == a) p->setRight(nullptr);
            } else if (a == root) {
                root = nullptr;   // nếu xóa root
            }
            n -= countNode(a);
            delete a;
        }
};

void printNode(BTreeNode<int>* p) {
    cout << p->getElem() << " ";
}

int main() {
    BTree<int> tree;

    // Chèn root
    tree.insert(nullptr, 1);                   // root = 1

    BTreeNode<int>* root = tree.getRoot();

    // Tầng 2
    tree.insert(root, 2);                      // left  của 1
    tree.insert(root, 3);                      // right của 1

    BTreeNode<int>* node2 = root->getLeft();
    BTreeNode<int>* node3 = root->getRight();

    // Tầng 3
    tree.insert(node2, 4);                     // left  của 2
    tree.insert(node2, 5);                     // right của 2
    tree.insert(node3, 6);                     // left  của 3 (3 chưa có left)

    cout << "Size: " << tree.size() << "\n";   // 6

    cout << "Pre-order:  ";
    tree.preOrder(tree.getRoot(), printNode);  // 1 2 4 5 3 6
    cout << "\n";

    cout << "In-order:   ";
    tree.inOrder(tree.getRoot(), printNode);   // 4 2 5 1 6 3
    cout << "\n";

    cout << "Post-order: ";
    tree.postOrder(tree.getRoot(), printNode); // 4 5 2 6 3 1
    cout << "\n";

    return 0;
}