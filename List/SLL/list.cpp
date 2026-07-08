#include <bits/stdc++.h>
using namespace std;

template <class T> //lưu nhiều dữ liệu 

class Node{
    public:
        T elem; 
        Node *next = NULL;      
        Node () : elem(0), next(nullptr) {}
        Node(T e, Node *N) {
            elem = e;
            next = N;
        }       
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Node<int> A(1, NULL);
    Node<int> B(2, NULL);
    Node<int> C(3, NULL);
    Node<int> *head = &A;
    // A.next = &B;
    // B.next = &C;
    // cout << &head << ' ' << head << "\n";
    head->next = &B;
    head->next->next = &C;
    while (head != NULL) {
        cout << head->elem << ' ';
        head = head->next;
    }
    cout << "\n";
    //thêm vào trước 
    Node<int> D(4, NULL);
    head = &D;
    head->next = &A;
    while (head != NULL) {
        cout << head->elem << ' ';
        head = head->next;
    }
    cout << "\n";
    //thêm vào sau
    Node<int> E(12, NULL);
    head = &D;
    C.next = &E;
    while (head != NULL) {
        cout << head->elem << ' ';
        head = head->next;
    }
    cout << '\n';
    head = &D;
    //chèn
    Node<int> Y(17,  NULL);
    // B.next =  &Y;
    // Y.next = &C;
    // head->next->next->next = &Y;
    // head->next->next->next->next = &C;
    Node <int> *temp = &Y;
    // cout << temp->elem <<' '<< temp->next;
    temp->next = &Y;
    B.next = temp;
    temp->next = &C;
    // cout << temp->elem <<' '<< temp->next << ' '<<temp;
    while (head != NULL) {
        cout << head->elem << ' ';
        head = head->next;
    }

    return 0;
}