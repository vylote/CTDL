// DLL.h
#ifndef DLL_H
#define DLL_H

#include <bits/stdc++.h>
using namespace std;

template <typename T> class List;

template <typename T>
class Node {
    private:
        T data;
        Node<T>* next;
        Node<T>* prev;
    public:
        Node(T data) : data(data), next(0), prev(0) {}

        T getData() { return this->data; }
        void setData(T data) { this->data = data; }

        void insert(Node<T>* p) {
            p->next = this->next;
            if (this->next) this->next->prev = p;
            this->next = p;
            p->prev = this;
        }

        friend class List<T>;
};

template <typename T>
class List {
    private:
        Node<T>* head;
        Node<T>* trail;

    public:
        List() : head(0), trail(0) {}

        class Iterator {
            Node<T>* ptr;
        public:
            Iterator(Node<T>* p) : ptr(p) {}
            T& operator*()  { return ptr->data; } // trả về tham chiếu, hay đơn giản là đây là vùng nhớ 'data' trong Node 
            T* operator->() { return &ptr->data; }  // T* là 1 con trỏ built-in, và ta hiểu như kiểu là int*a = &b
            Node<T>* node() { return ptr; } 
            Iterator& operator++() { ptr = ptr->next; return *this; }
            bool operator!=(const Iterator& other) { return ptr != other.ptr; }
        };

        Iterator begin() { return Iterator(head); }
        Iterator end()   { return Iterator(0); }

        void remove(Node<T>* p) {
            if (p->prev) p->prev->next = p->next;
            else head = p->next;
            if (p->next) p->next->prev = p->prev;
            else trail = p->prev;
            delete p;
        }

        void push_back(Node<T>* p) {
            if (!trail) head = trail = p;
            else { trail->insert(p); trail = p; }
        }

        void push_front(Node<T>* p) {
            if (!head) { head = trail = p; return; }
            p->next = head;
            head->prev = p;
            p->prev = 0;
            head = p;
        }

        void push(int i, Node<T>* p) {
            if (i == 0) { push_front(p); return; }
            Node<T>* temp = head;
            while (i > 1 && temp->next) {
                temp = temp->next;
                i--;
            }
            temp->insert(p);
            if (temp == trail) trail = p;
        }

        bool empty() { return head == 0; }

        void print() {
            for (auto it = begin(); it != end(); ++it)
                cout << (*it) << " ";
            cout << "\n";
        }
};

#endif