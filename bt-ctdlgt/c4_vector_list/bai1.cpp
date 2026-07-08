#include <bits/stdc++.h>
using namespace std;

template <class T>
class Vector
{
private:
    T *a;
    int n, limit;

public:
    Vector() : n(0), limit(1) { a = new T[limit]; }
    ~Vector() { delete[] a; }
    int size() { return n; }

    void erase(int pos)
    {
        if (pos < 0 || pos >= n)
            return;
        for (int i = pos; i < n - 1; ++i)
            a[i] = a[i + 1];
        --n;
    }

    void assign(int i, T val)
    {
        if (i < 0 || i >= n)
            return;
        a[i] = val;
    }

    void pushBack(T val)
    {
        if (n == limit)
        {
            limit *= 2;
            T *b = new T[limit];
            for (int i = 0; i < n; ++i)
                b[i] = a[i];
            delete[] a;
            a = b;
        }
        a[n++] = val;
    }
    void insert(int pos, T val)
    {
        if (pos < 0 || pos > n)
            return;
        if (n == limit)
        {
            limit *= 2;
            T *b = new T[limit];
            for (int i = 0; i < n; ++i)
                b[i] = a[i];
            delete[] a;
            a = b;
        }
        for (int i = n; i > pos; i--)
            a[i] = a[i - 1];
        a[pos] = val;
        n++;
    }
    T &operator[](int i) { return a[i]; }
    class Iterator
    {
    private:
        T *ptr;

    public:
        Iterator(T *ptr) : ptr(ptr) {}
        T &operator*() { return *ptr; }
        Iterator &operator++()
        {
            ++ptr;  
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp(*this); // Copy giá trị cũ
            ++ptr;               // Tăng con trỏ
            return tmp;          // Trả về giá trị cũ (không phải reference)
        }
        bool operator!=(const Iterator &a) { return ptr != a.ptr; }
    };

    Iterator begin() { return Iterator(a); }
    Iterator end() { return Iterator(a + n); }
};

// int main() {
//     Vector<int> v;
//     v.pushBack(1);
//     v.pushBack(2);
//     v.pushBack(3);
//     v.insert(1,4);
//     for (auto it = v.begin(); it != v.end(); it++) {
//         cout << *it << " ";
//     }
//     cout << "\n" << v[1];
//     for (int i = 0; i < v.size(); ++i)
//         cout << v[i] << " ";
// }