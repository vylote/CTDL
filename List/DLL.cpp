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
        Node(T data) {
            this->data = data;
            this->next = 0;
            this->prev = 0;
        }

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
        List() {
            this->head = 0;
            this->trail = 0;
        }

        void remove(Node<T>* p) {
            if (p->prev) p->prev->next = p->next;
            else head = p->next;          // p là head
            if (p->next) p->next->prev = p->prev;
            else trail = p->prev;         // p là trail
            delete p;
        }

        void push_back(Node<T>* p) {
            if (!trail) {
                head = trail = p;
            } else {
                trail->insert(p);
                trail = p;
            }
        }

        void push_front(Node<T>* p) {
            if (!head) {
                head = trail = p;
            } else {
                p->next = head;
                head->prev = p;
                p->prev = 0;
                head = p;
            }
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

        void print() {
            Node<T>* temp = head;
            while (temp) {
                cout << temp->getData() << " ";
                temp = temp->next;
            }
            cout << "\n";
        }
};

int main() {
    List<int> l;
    l.push_back(new Node<int>(1));
    l.push_back(new Node<int>(2));
    l.push_back(new Node<int>(3));
    l.push_front(new Node<int>(0));
    l.push(2, new Node<int>(99));
    l.print();  // 0 1 99 2 3
}