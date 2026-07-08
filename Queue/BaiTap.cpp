#include <bits/stdc++.h>
using namespace std;
// cai dat queue bang mang

template<class T>

class Queue{
    class Node{
        public:
        T data;
        Node* next = nullptr;
        Node(T data) : data(data), next(nullptr) {} 
    };
    Node* first;
    Node* last;
    int N;
    public:
        Queue() : first(nullptr), last(nullptr), N(0) {}
        ~Queue() {
            while(!isEmpty()) {
                dequeue();
            }
        }
        bool isEmpty() {
            return first == nullptr; // return last = nullptr;
        }
        void enqueue(T value) {
            Node* newNode = new Node(value);
            if (last == nullptr) {
                first = last = newNode;
            }
            else {
                last = last->next;
                last = newNode;
            }
            N++;
        }

        //remove an element from queue pop()
        void dequeue() {
            if (isEmpty()) {
                std::cerr << "Queue is empty";
                return;
            }
            Node* temp = first;
            first = first->next;
            if (first == nullptr) {
                last = nullptr;
            }
            delete temp;
            --N;
        }
        int size() {
            return N;
        }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Queue<int> A;
    A.enqueue(12);
    A.enqueue(13);
    A.enqueue(14);
    
    cout << A.size() << endl;
    A.print();
    return 0;
}