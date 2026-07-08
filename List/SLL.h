#pragma once
#include <iostream>
using namespace std;

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

template <typename T>
class SLL
{
private:
    Node<T> *head;
    Node<T> *trail;

public:
    SLL() : head(nullptr), trail(nullptr) {}
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
    void pushBack(Node<T> *a)
    {
        if (trail == nullptr)
        {
            head = trail = a;
            return;
        }
        trail->setNext(a);
        trail = a;
    }
    void pushFront(Node<T> *a)
    {
        if (head == nullptr)
        {
            head = trail = a;
            return;
        }
        a->setNext(head);
        head = a;
    }
    void push(int i, Node<T> *a)
    {
        if (i == 0)
        {
            pushFront(a);
            return;
        }
        Node<T> *tmp = head;
        int pos = 0;
        while (pos < i && tmp->getNext())
        {
            tmp = tmp->getNext();
            pos++;
        }
        tmp->insert(a);
    }

    void insertOrder(T val)
    {
        Node<T> *newNode = new Node<T>(val);
        if (head == nullptr)
        {
            head = trail = newNode;
            return;
        }

        Node<T> *cur = head;
        Node<T> *prev = nullptr;

        while (cur != nullptr)
        {
            if (cur->getData() == val)
            {
                delete newNode;
                return;
            }
            if (cur->getData() > val)
                break;
            prev = cur;
            cur = cur->getNext();
        }

        if (prev == nullptr)
        {
            pushFront(newNode);
            return;
        }
        if (cur == nullptr)
        {
            pushBack(newNode);
            return;
        }
        prev->setNext(newNode);
        newNode->setNext(cur);
    }

    class Iterator
    {
    private:
        Node<T> *ptr;

    public:
        Iterator(Node<T> *p) : ptr(p) {}
        // T& để tránh copy, nhưng đồng nghĩa với việc cho phép sửa data
        // Nếu cần read-only thì dùng const T& (ConstIterator)
        T &operator*() { return ptr->getData(); }   // trả về T& -> đọc/sửa được giá trị thật
        T *operator->() { return &ptr->getData(); } // trả về T* -> để C++ tự dereference tiếp
        Node<T> *node() { return ptr; }             // trả thẳng con trỏ Node, dùng khi cần thao tác nội bộ list
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