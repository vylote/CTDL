#include <bits/stdc++.h>
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

template<class T>
class Queue{
    private:
        Node<T>* head, *tail;
        int N;
    public:
        Node<T>* getHead() {return head;}
        Queue() : head(nullptr), tail(nullptr), N(0) {}
        ~Queue() {
            Node<T>* cur = head;
            while (cur != nullptr) {
                Node<T>* tmp = cur;
                cur = cur->getNext();
                delete tmp;
            }
            head = tail = nullptr;
        }
        bool empty() {return N==0;}
        int size() {return N;}
        T front() {return head->getData();}
        T back() {return tail->getData();}
        void pop() {
            if (empty()) return;
            Node<T>* tmp = head;
            head = head->getNext();
            delete tmp;
            N--;

            if (head == nullptr)
                tail = nullptr;
        }
        void push(T o) {
            Node<T>* p = new Node<T>(o);
            if (empty()) {
                head = tail = p;
                N++;
                return;
            }
            tail->setNext(p);
            tail = p;
            N++;
        }
};

int main() {
    Queue<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    Node<int>* l = a.getHead();
    while (l != nullptr) {
        cout << l->getData() << " ";
        l = l->getNext();
    }
}