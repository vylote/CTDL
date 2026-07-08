#include <bits/stdc++.h>
using namespace std;
#ifndef __arraystack__cpp
#define __arraystack__cpp
template <class T>

class Stack{
    unsigned cap, num;
    T *buff;
    public:
        Stack() : buff(nullptr), cap(0), num(0) {}
        void reserve(unsigned newcap) {
            if (newcap < cap) return;
            cap = newcap;
            T *temp = new T[cap];
            for (int i = 0; i < num; ++i) temp[i] = buff[i];
            if (buff) delete[] buff;
            buff = temp; 
        }
        int size() {return num;}
        bool empty() {return num = 0;}
        T &top() {return buff[num-1];}
        void pop() {if(num) num--;}
        void push(T x) {
            if (cap == num) reserve(cap*2+2);
            buff[num++] = x;
        }
};
#endif