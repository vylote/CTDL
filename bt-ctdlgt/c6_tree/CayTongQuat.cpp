#include <bits/stdc++.h>
using namespace std;

template <class T>
class TreeNode
{
private:
    T elem;
    TreeNode *parent;
    vector<TreeNode *> child;

public:
    TreeNode(T e) : elem(e), parent(nullptr) {}

    // Cấm copy (Rule of Three — giống BTree)
    TreeNode(const TreeNode&)            = delete;
    TreeNode& operator=(const TreeNode&) = delete;

    ~TreeNode()
    {
        for (TreeNode *c : child)
            delete c;
    }

    T getElem() const { return elem; }
    void setElem(T e) { elem = e; }

    TreeNode *getParent() const { return parent; }
    void setParent(TreeNode *p) { parent = p; }

    bool hasChild() const { return !child.empty(); }

    // getChild(int i) — lấy con thứ i
    TreeNode *getChild(int i) { return child[i]; }

    // getChild() — trả về danh sách con (đổi tên từ getChildren)
    vector<TreeNode *> &getChild() { return child; }

    TreeNode *insertChild(T e)
    {
        TreeNode *x = new TreeNode(e);
        x->parent = this;
        child.push_back(x);
        return x;
    }
};

template <class T>
class Tree
{
private:
    TreeNode<T> *Root;
    int n;

public:
    Tree() : Root(nullptr), n(0) {}

    // Cấm copy
    Tree(const Tree&)            = delete;
    Tree& operator=(const Tree&) = delete;

    ~Tree() { delete Root; }

    TreeNode<T> *root() { return Root; }

    void setRoot(T e)
    {
        delete Root;
        Root = new TreeNode<T>(e);
        n = 1;
    }

    int size() { return n; }

    // Slide: int isEmpty()  →  1 nếu rỗng, -1 nếu không
    int isEmpty() { return Root == nullptr ? 1 : -1; }

    // Slide: int isRoot/isInternal/isExternal  →  1/-1, thêm nullptr check
    int isRoot(TreeNode<T> *p)
    {
        if (p == nullptr) return -1;
        return p == Root ? 1 : -1;
    }

    int isInternal(TreeNode<T> *p)
    {
        if (p == nullptr) return -1;
        return p->hasChild() ? 1 : -1;
    }

    int isExternal(TreeNode<T> *p)
    {
        if (p == nullptr) return -1;
        return !p->hasChild() ? 1 : -1;
    }

    // Slide: void insert(TreeNode *parent, element)  →  đổi về void
    void insert(TreeNode<T> *parent, T e)
    {
        if (parent == nullptr)
        {
            if (Root != nullptr) return;
            Root = new TreeNode<T>(e);
            n = 1;
            return;
        }
        parent->insertChild(e);
        n++;
    }

    int countNode(TreeNode<T> *p)
    {
        if (p == nullptr) return 0;
        int cnt = 1;
        for (auto c : p->getChild())   // đổi getChildren() → getChild()
            cnt += countNode(c);
        return cnt;
    }

    void remove(TreeNode<T> *p)
    {
        if (p == nullptr) return;

        if (p == Root)
        {
            delete Root;
            Root = nullptr;
            n = 0;
            return;
        }

        TreeNode<T> *par = p->getParent();
        auto &v = par->getChild();         // đổi getChildren() → getChild()
        auto it = std::find(v.begin(), v.end(), p);
        if (it != v.end()) v.erase(it);
        n -= countNode(p);
        delete p;
    }

    void removeKeepChild(TreeNode<T> *p)
    {
        if (p == nullptr || p == Root) return;

        TreeNode<T> *par = p->getParent();
        auto &sibling = par->getChild();   // đổi getChildren() → getChild()
        auto pos = std::find(sibling.begin(), sibling.end(), p);
        if (pos == sibling.end()) return;

        int idx = pos - sibling.begin();
        sibling.erase(pos);

        for (auto c : p->getChild())       // đổi getChildren() → getChild()
        {
            c->setParent(par);
            sibling.insert(sibling.begin() + idx, c);
            idx++;
        }

        p->getChild().clear();
        delete p;
        n--;
    }

    void preOrder(TreeNode<T> *p, void (*visit)(TreeNode<T> *))
    {
        if (p == nullptr) return;
        visit(p);
        for (auto c : p->getChild())       // đổi getChildren() → getChild()
            preOrder(c, visit);
    }

    void postOrder(TreeNode<T> *p, void (*visit)(TreeNode<T> *))
    {
        if (p == nullptr) return;
        for (auto c : p->getChild())       // đổi getChildren() → getChild()
            postOrder(c, visit);
        visit(p);
    }

    void inOrder(TreeNode<T> *p, void (*visit)(TreeNode<T> *))
    {
        if (p == nullptr) return;
        auto &ch = p->getChild();          // đổi getChildren() → getChild()
        if (!ch.empty()) inOrder(ch[0], visit);
        visit(p);
        for (size_t i = 1; i < ch.size(); ++i)
            inOrder(ch[i], visit);
    }

    void levelOrder(void (*visit)(TreeNode<T> *))
    {
        if (Root == nullptr) return;
        queue<TreeNode<T> *> q;
        q.push(Root);
        while (!q.empty())
        {
            auto cur = q.front(); q.pop();
            visit(cur);
            for (auto c : cur->getChild())  // đổi getChildren() → getChild()
                q.push(c);
        }
    }

    int depth(TreeNode<T> *p)
    {
        int d = 0;
        while (p != Root) { d++; p = p->getParent(); }
        return d;
    }

    int height(TreeNode<T> *p)
    {
        if (p == nullptr) return -1;
        int h = -1;
        for (auto c : p->getChild())        // đổi getChildren() → getChild()
            h = max(h, height(c));
        return h + 1;
    }

    TreeNode<T> *find(TreeNode<T> *p, T value)
    {
        if (p == nullptr) return nullptr;
        if (p->getElem() == value) return p;
        for (auto c : p->getChild())        // đổi getChildren() → getChild()
        {
            auto ans = find(c, value);
            if (ans) return ans;
        }
        return nullptr;
    }
};

void printNode(TreeNode<int> *p) {
    cout << p->getElem() << " ";
}

int main() {
    Tree<int> tree;

    // ── Dựng cây ──────────────────────────────
    tree.insert(nullptr, 1);                  // root = 1

    TreeNode<int> *r = tree.root();
    tree.insert(r, 2);                        // con của 1
    tree.insert(r, 3);
    tree.insert(r, 4);

    TreeNode<int> *n2 = r->getChild(0);      // node 2
    TreeNode<int> *n4 = r->getChild(2);      // node 4

    tree.insert(n2, 5);                       // con của 2
    tree.insert(n2, 6);
    tree.insert(n4, 7);                       // con của 4

    // ── size ──────────────────────────────────
    cout << "size      : " << tree.size() << "\n";        // 7
    cout << "isEmpty   : " << tree.isEmpty() << "\n";     // -1

    // ── is* ───────────────────────────────────
    cout << "isRoot(1) : " << tree.isRoot(r) << "\n";           // 1
    cout << "isRoot(2) : " << tree.isRoot(n2) << "\n";          // -1
    cout << "isInternal(2): " << tree.isInternal(n2) << "\n";   // 1
    cout << "isExternal(3): " << tree.isExternal(r->getChild(1)) << "\n"; // 1 (node 3 không có con)

    // ── duyệt cây ─────────────────────────────
    cout << "\npreOrder  : "; tree.preOrder(r, printNode);   // 1 2 5 6 3 4 7
    cout << "\ninOrder   : "; tree.inOrder(r, printNode);    // 5 2 6 1 3 4 7
    cout << "\npostOrder : "; tree.postOrder(r, printNode);  // 5 6 2 3 7 4 1
    cout << "\nlevelOrder: "; tree.levelOrder(printNode);    // 1 2 3 4 5 6 7
    cout << "\n";

    // ── depth / height ────────────────────────
    TreeNode<int> *n5 = n2->getChild(0);
    cout << "\ndepth(5)  : " << tree.depth(n5) << "\n";     // 2
    cout << "height(1) : " << tree.height(r)  << "\n";     // 2
    cout << "height(2) : " << tree.height(n2) << "\n";     // 1

    // ── find ──────────────────────────────────
    TreeNode<int> *found = tree.find(r, 6);
    cout << "\nfind(6)   : " << (found ? found->getElem() : -1) << "\n"; // 6
    cout << "find(99)  : " << (tree.find(r, 99) ? "found" : "null") << "\n"; // null

    // ── remove node lá ────────────────────────
    cout << "\n--- remove node 5 ---\n";
    tree.remove(n5);
    cout << "size sau remove: " << tree.size() << "\n";     // 6
    cout << "preOrder sau  : "; tree.preOrder(r, printNode); // 1 2 6 3 4 7
    cout << "\n";

    // ── removeKeepChild (xóa node 2, giữ con 6) ──
    cout << "\n--- removeKeepChild node 2 ---\n";
    tree.removeKeepChild(n2);
    cout << "size sau removeKeepChild: " << tree.size() << "\n"; // 5
    cout << "levelOrder sau: "; tree.levelOrder(printNode); // 1 6 3 4 7
    cout << "\n";

    return 0;
}