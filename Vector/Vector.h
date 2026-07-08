#pragma once

template<typename T>
class Vector {
    int n, limit;
    T *a;
public:
    Vector() {
        n = 0;
        limit = 1;
        a = new T[limit];
    }

    ~Vector() {
        delete[] a;
    }

    int size() { return n; }

    void push_back(T x) {
        if (n == limit) {
            limit *= 2;
            T *b = new T[limit];
            for (int i = 0; i < n; i++) b[i] = a[i];
            delete[] a;
            a = b;
        }
        a[n++] = x;
    }

    void erase(int i) {
        if (i < 0 || i >= n) return;
        for (int j = i; j < n - 1; j++) a[j] = a[j + 1];
        n--;
    }

    void edit(int i, T x) {
        if (i < 0 || i >= n) return;
        a[i] = x;
    }

    T get(int i) {
        return a[i];
    }

    T& operator[](int i) {
        return a[i];
    }

    // Iterator
    class Iterator {
        T *ptr;
    public: 
        Iterator(T *p) : ptr(p) {}
        T& operator*()  { return *ptr; }
        T* operator->() { return ptr; }
        Iterator& operator++() { ptr++; return *this; }
        bool operator!=(const Iterator& other) { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(a); }
    Iterator end()   { return Iterator(a + n); }
};