#include <bits/stdc++.h>
using namespace std;

template<class T>
class Stack {
    private:
        T* s;
        int t, capacity; //t: luu chi so phan tu thu n-1
    public:
        Stack(int cap=8) : t(-1), capacity(cap) {s = new T[cap];}
        ~Stack() {delete[] s;}
        int size() {return t+1;}
        bool isEmpty() {return t<0;}
        void push(T val) {
            if (t+1 == capacity) {
                capacity *= 2;
                T* tmp = new T[capacity];
                for (int i=0;i<=t;++i) tmp[i]=s[i];
                delete s;
                s = tmp;
            }
            s[++t]=val;
        }
        void pop() {
            if (t<0) return;
            --t;
        }
        T top() {return s[t];}
};

int main() {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << s.top();
}