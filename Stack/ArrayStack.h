#pragma once
#include <stdexcept>

template<typename T>
class ArrayStack {
    T*  s;
    int t;
    int capacity;

public:
    ArrayStack(int cap = 8) : t(-1), capacity(cap) {
        s = new T[capacity];
    }

    ~ArrayStack() { delete[] s; }

    int  size()    { return t + 1; }
    bool isEmpty() { return t < 0; }

    void push(T o) {
        if (size() == capacity) {
            capacity *= 2;
            T* tmp = new T[capacity];
            for (int i = 0; i <= t; i++)   // copy toan bo phan tu cu
                tmp[i] = s[i];
            delete[] s;
            s = tmp;
        }
        s[++t] = o;                        // chi gan 1 lan, sau khi s da san sang
    }

    void pop(T& o) {
        if (isEmpty())
            throw std::underflow_error("Stack rong!");
        o = s[t--];
    }

    T top() {
        if (isEmpty())
            throw std::underflow_error("Stack rong!");
        return s[t];
    }
};
