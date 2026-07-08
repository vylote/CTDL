#include <bits/stdc++.h>
using namespace std;
#ifndef __nodestack__cpp
#define __nodestack__cpp

template<class T>
class Stack {
    class Node {
    T elem;
    Node *next;
    public:
    Node() : elem(0), next(nullptr) {}
    Node(T elem, Node *next = nullptr) : elem(elem), next(next) {}
    Node* getNext() {return next;}
    T& getElem() {return elem;}
};
    unsigned int num;
    Node *H; //head
    public:
        Stack() : num(0), H(nullptr) {}
        unsigned int size() {return num;}
        bool empty() {return num == 0j;}
        T& top() {return H->getElem();}
        void pop() { 
            if (num <= 1) {
                Node *newNode = new Node;
                H = newNode;
            }
            H = H->getNext(); num--;
        }
        void pushElem(T elem) {
            H = new Node(elem, H); num++;
        }
        void print() const{
            Node *temp = H;
            while (temp != nullptr) {
                cout << temp->getElem() << " ";
                temp = temp->getNext();
            }
            cout << "\n";
        }
};
#endif

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Stack<int> s;
    s.pushElem(12);
    s.pop();
    s.print();
    return 0;
}
