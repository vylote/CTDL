#include <bits/stdc++.h>
using namespace std;

template <typename Key, typename T>
class Node
{
private:
    Key key;
    T data;
    Node *next;

public:
    Node(Key key, T data) : key(key), data(data), next(nullptr) {}
    Node() : key(), data(), next(nullptr) {}

    void insert(Node<Key, T> *p)
    {
        p->next = this->next;
        this->next = p;
    }

    T &getData() { return this->data; }
    void setData(T data) { this->data = data; }

    Node<Key, T> *getNext() { return this->next; }
    void setNext(Node<Key, T> *p) { this->next = p; }

    Key getKey() const
    {
        return key;
    }

    void setKey(Key key)
    {
        this->key = key;
    }
};

template <typename Key, typename T>
class SLL
{
private:
    Node<Key, T> *head;
    Node<Key, T> *trail;

public:
    SLL() : head(nullptr), trail(nullptr) {}
    ~SLL()
    {
        Node<Key, T> *cur = head;
        while (cur != nullptr)
        {
            Node<Key, T> *tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }
        head = trail = nullptr;
    }

    bool remove(Key key)
    {
        Node<Key, T> *cur = head;
        Node<Key, T> *pre = nullptr;

        while (cur)
        {
            if (cur->getKey() == key)
            {
                if (pre == nullptr)
                {
                    head = cur->getNext();

                    if (head == nullptr)
                        trail = nullptr;
                }
                else
                {
                    pre->setNext(cur->getNext());

                    if (cur == trail)
                        trail = pre;
                }

                delete cur;
                return true;
            }

            pre = cur;
            cur = cur->getNext();
        }

        return false;
    }

    Node<Key, T> *getHead() const
    {
        return head;
    }

    void pushBack(Node<Key, T> *a)
    {
        if (trail == nullptr)
        {
            head = trail = a;
            return;
        }
        trail->setNext(a);
        trail = a;
    }
    void pushFront(Node<Key, T> *a)
    {
        if (head == nullptr)
        {
            head = trail = a;
            return;
        }
        a->setNext(head);
        head = a;
    }
    void push(int i, Node<Key, T> *a)
    {
        if (i == 0)
        {
            pushFront(a);
            return;
        }
        Node<Key, T> *tmp = head;
        int pos = 0;
        while (pos < i && tmp->getNext())
        {
            tmp = tmp->getNext();
            pos++;
        }
        tmp->insert(a);
    }

    class Iterator
    {
    private:
        Node<Key, T> *ptr;

    public:
        Iterator(Node<Key, T> *p) : ptr(p) {}
        // T& để tránh copy, nhưng đồng nghĩa với việc cho phép sửa data
        // Nếu cần read-only thì dùng const T& (ConstIterator)
        T &operator*() { return ptr->getData(); }   // trả về T& -> đọc/sửa được giá trị thật
        T *operator->() { return &ptr->getData(); } // trả về T* -> để C++ tự dereference tiếp
        Node<Key, T> *node() { return ptr; }        // trả thẳng con trỏ Node, dùng khi cần thao tác nội bộ list
        Iterator &operator++()
        {
            ptr = ptr->getNext();
            return *this;
        } //*this là deference con trỏ this->chính là object,
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ptr = ptr->getNext();
            return tmp;
        }
        bool operator!=(const Iterator &other) { return ptr != other.ptr; }
    };

    // CHÚ Ý: begin()/end() const chỉ cam kết không sửa head/trail của SLL,
    // KHÔNG ngăn sửa data bên trong node qua Iterator (vì operator* trả về T&)
    // Để chặt hoàn toàn cần implement thêm ConstIterator riêng
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

template <typename Key, typename T>
class HashTable
{
private:
    SLL<Key, T> *table;
    int m;
    int n;

public:
    HashTable(int m)
    {
        this->m = m;
        n = 0;
        table = new SLL<Key, T>[m];
    }

    ~HashTable()
    {
        delete[] table;
    }

    int hash(Key key)
    {
        return key % m;
    }

    Node<Key, T> *Add(Key key, T obj)
    {
        int index = hash(key);

        Node<Key, T> *p = new Node<Key, T>(key, obj);

        table[index].pushFront(p);

        n++;

        return p;
    }

    Node<Key, T> *Find(Key key)
    {
        int index = hash(key);

        Node<Key, T> *cur = table[index].getHead();

        while (cur)
        {
            if (cur->getKey() == key)
                return cur;

            cur = cur->getNext();
        }

        return nullptr;
    }

    bool Contains(Key key)
    {
        return Find(key) != nullptr;
    }

    void Remove(Key key)
    {
        int index = hash(key);

        if (table[index].remove(key))
            n--;
    }

    int Count()
    {
        return n;
    }
};

int main()
{
    HashTable<int, string> ht(10);

    ht.Add(15, "A");
    ht.Add(25, "B");
    ht.Add(35, "C");

    cout << ht.Count() << endl; // 3

    cout << ht.Contains(25); // 1

    cout << ht.Find(35)->getData(); // C

    ht.Remove(25);

    cout << ht.Count(); // 2
}