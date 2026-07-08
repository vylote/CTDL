// =====================================================================
// FILE GOP: SLL.h (co them log o ctor) + bai2() de test NRVO
// Bien dich:
//   Ban NRVO BAT (mac dinh):  g++ -std=c++17 -O0 test_nrvo.cpp -o test_on
//   Ban NRVO TAT:             g++ -std=c++17 -O0 -fno-elide-constructors test_nrvo.cpp -o test_off
// Chay: ./test_on   hoac   ./test_off
// =====================================================================
#include <iostream>
using namespace std;

// ---------------------- Node ----------------------
template <typename T>
class Node
{
private:
    T data;
    Node *next;

public:
    Node(T data) : data(data), next(nullptr) {}
    Node() : data(), next(nullptr) {}

    void insert(Node<T> *p)
    {
        p->next = this->next;
        this->next = p;
    }

    T &getData() { return this->data; }
    void setData(T data) { this->data = data; }
    Node<T> *getNext() { return this->next; }
    void setNext(Node<T> *p) { this->next = p; }
};

// ---------------------- SLL (co log de xem NRVO) ----------------------
template <typename T>
class SLL
{
private:
    Node<T> *head;
    Node<T> *trail;

public:
    SLL() : head(nullptr), trail(nullptr)
    {
        cout << "[default ctor]  this=" << this << "\n";
    }

    ~SLL()
    {
        Node<T> *cur = head;
        while (cur != nullptr)
        {
            Node<T> *tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }
        head = trail = nullptr;
    }

    SLL(const SLL &other) : head(nullptr), trail(nullptr)
    {
        cout << "[COPY ctor]     this=" << this << "  from=" << &other << "\n";
        for (Iterator it = other.begin(); it != other.end(); ++it)
            pushBack(new Node<T>(*it));
    }

    SLL &operator=(const SLL &other)
    {
        cout << "[COPY assign]   this=" << this << "  from=" << &other << "\n";
        if (this == &other)
            return *this;
        Node<T> *cur = head;
        while (cur != nullptr)
        {
            Node<T> *tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }
        head = trail = nullptr;
        for (Iterator it = other.begin(); it != other.end(); ++it)
            pushBack(new Node<T>(*it));
        return *this;
    }

    SLL(SLL &&other) noexcept : head(other.head), trail(other.trail)
    {
        cout << "[MOVE ctor]     this=" << this << "  from=" << &other << "\n";
        other.head = nullptr;
        other.trail = nullptr;
    }

    SLL &operator=(SLL &&other) noexcept
    {
        cout << "[MOVE assign]   this=" << this << "  from=" << &other << "\n";
        if (this == &other)
            return *this;
        Node<T> *cur = head;
        while (cur != nullptr)
        {
            Node<T> *tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }
        head = other.head;
        trail = other.trail;
        other.head = nullptr;
        other.trail = nullptr;
        return *this;
    }

    void pushBack(Node<T> *a)
    {
        if (trail == nullptr) { head = trail = a; return; }
        trail->setNext(a);
        trail = a;
    }

    void pushFront(Node<T> *a)
    {
        if (head == nullptr) { head = trail = a; return; }
        a->setNext(head);
        head = a;
    }

    class Iterator
    {
    private:
        Node<T> *ptr;
    public:
        Iterator(Node<T> *p) : ptr(p) {}
        T &operator*() { return ptr->getData(); }
        T *operator->() { return &ptr->getData(); }
        Node<T> *node() { return ptr; }
        Iterator &operator++() { ptr = ptr->getNext(); return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ptr = ptr->getNext(); return tmp; }
        bool operator!=(const Iterator &other) { return ptr != other.ptr; }
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }

    void input()
    {
        cout << "n: ";
        int n;
        cin >> n;
        cout << n << " phan tu: ";
        while (n--)
        {
            T val;
            cin >> val;
            pushBack(new Node<T>(val));
        }
    }

    void print() const
    {
        for (Iterator it = begin(); it != end(); ++it)
            cout << *it << " ";
        cout << endl;
    }

    // Ham can test: co in them dia chi newSLL truoc khi return
    SLL merge(const SLL &a)
    {
        cout << "  -> tao newSLL trong merge()...\n     ";
        SLL newSLL;
        Iterator it1 = begin();
        Iterator it2 = a.begin();
        while (it1 != this->end() && it2 != a.end())
        {
            if (*it1 < *it2) { newSLL.pushBack(new Node<T>(*it1)); it1++; }
            else { newSLL.pushBack(new Node<T>(*it2)); it2++; }
        }
        while (it1 != this->end()) { newSLL.pushBack(new Node<T>(*it1)); it1++; }
        while (it2 != a.end()) { newSLL.pushBack(new Node<T>(*it2)); it2++; }
        cout << "  -> dia chi &newSLL = " << &newSLL << "  (chuan bi return)\n";
        return newSLL;
    }
};

// ---------------------- bai2() ----------------------
void bai2()
{
    SLL<int> a, b;
    cout << "ds a:\n";
    a.input();
    cout << "ds b:\n";
    b.input();

    cout << "goi merge, dia chi bien 'res' se duoc gan sau day...\n";
    SLL<int> res = a.merge(b);
    cout << "dia chi &res      = " << &res << "\n";

    cout << "ds sau tron: ";
    res.print();
}

// ---------------------- main ----------------------
int main()
{
    cout << "=== Bai 2 (test NRVO) ===\n";
    bai2();
    return 0;
}