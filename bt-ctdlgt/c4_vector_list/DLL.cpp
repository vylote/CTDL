#include <bits/stdc++.h>
using namespace std;

template<class T>
class Node {
    private:
        T data;
        Node* next, *prev;
    public:
        Node() : data(), next(nullptr), prev(nullptr) {}
        Node(T data) : data(data), next(nullptr), prev(nullptr) {}
        T getData() {return data;}
        Node<T>* getNext() {return next;} 
        Node<T>* getPrev() {return prev;} 
        void setData(T val) {data = val;}
        void setNext(Node<T>* n) {next = n;}
        void setPrev(Node<T>* p) {prev=p;}
        void insert(Node<T>* a) {
            if (!a) return;
            a->setNext(this->getNext());
            if (this->getNext()) 
                this->getNext()->setPrev(a);
            this->setNext(a);
            a->setPrev(this);
        }
};

template<class T>
class DLL {
    private:
        Node<T>* head;
        Node<T>* tail;
    public:
        DLL() : head(nullptr), tail(nullptr) {}
        ~DLL() {
            Node<T>* cur = head;
            while(cur != nullptr) {
                Node<T> *tmp=cur->getNext();
                if (tmp != nullptr)
                    tmp->setPrev(nullptr);
                delete cur;
                cur = tmp;
            }
            head = tail = nullptr;
        }
        int size() {
            Node<T>* cur = head;
            int res = 0;
            while(cur != nullptr) {
                res++;
                cur = cur->getNext();
            }
            return res;
        }

        void erase(int i) {
            if (i < 0||i>=size()) return;
            if (i == 0) {
                Node<T>* tmp = head;
                head = head->getNext();
                if (head) head->setPrev(nullptr);
                else tail = nullptr;
                delete tmp;
                return; 
            }
            Node<T>* cur = head;
            Node<T>* tmp;
            int j = 0;
            while (j < i && cur->getNext()) {
                tmp = cur;
                cur = cur->getNext();
                j++;
            }
            if (cur->getNext() == nullptr) {
                tmp->setNext(nullptr);
                delete cur;
                tail = tmp;
                return;
            } 

            tmp->setNext(cur->getNext());
            cur->getNext()->setPrev(tmp);
            delete cur;
        }

        void pushBack(Node<T>* a) {
            if (tail == nullptr) {
                head = tail = a;
                return;
            }
            Node<T>* cur = head; Node<T>* tmp;
            while (cur->getNext() != nullptr) {
                cur = cur->getNext();
                tmp = cur;
            }
            tmp->setNext(a);
            a->setPrev(tmp);
            tail = a;
        }
        void pushFront(Node<T>* a) {
            if (head == nullptr) {
                head = tail = a;
                return;
            }
            a->setNext(head);
            head->setPrev(a);
            a->setPrev(nullptr);
            head = a;
        }
        void push(int i, Node<T>* a) {
            if (i == 0 || head == nullptr) {
                pushFront(a);
                return;
            }
            Node<T>* cur = head;
            int j = 0;
            while (j < i && cur->getNext()) {
                cur = cur->getNext();
                j++;
            }
            if (cur->getNext() == nullptr) {
                pushBack(a);
                return;
            }
            cur->getPrev()->insert(a);
        }

        class Iterator {
            private:
                Node<T>* ptr;
            public:
                Iterator(Node<T>* p) : ptr(p) {}
                T operator*() {return ptr->getData();}
                Iterator& operator++() {ptr = ptr->getNext(); return *this;}
                bool operator!=(const Iterator& a) {return ptr != a.ptr;}
        };

        Iterator begin() {return Iterator(head);}
        Iterator end() {return Iterator(nullptr);}
};

int main() {
    Node<int>* a(new Node<int>(1));
    Node<int>* b(new Node<int>(2));
    Node<int>* c(new Node<int>(3));
    Node<int>* d(new Node<int>(4));
    DLL<int> e;
    e.pushBack(a);
    e.pushFront(c);
    e.push(0,b);
    e.push(1,d);
    e.erase(0);
    for (DLL<int>::Iterator it = e.begin(); it != e.end(); ++it) {
        cout << *it << " ";
    }
}