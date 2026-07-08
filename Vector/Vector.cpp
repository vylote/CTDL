#include <iostream>
using namespace std;

template<class T>
class Iterator;
template<class T>
class ReverseIterator;
template<class T>
class Vector {
private:
    unsigned int cap, num;
    T *buff;

public:
    Vector() : cap(0), num(0), buff(nullptr) {}
    Vector(unsigned int n) : cap(n), num(n), buff(new T[n]) {}
    Vector(unsigned int n, T x) : cap(n), num(n), buff(new T[n]) {
        for (unsigned int i = 0; i < n; ++i) buff[i] = x;
    }
    ~Vector() { delete[] buff; }

    friend istream& operator >> (istream &is, Vector<T> &v) {
        for (unsigned int i = 0; i < v.num; ++i) is >> v.buff[i];
        return is;
    }
    friend ostream& operator << (ostream &os, const Vector<T> &v) {
        for (unsigned int i = 0; i < v.num; ++i) os << v.buff[i] << " ";
        os << "\n";
        return os;
    }

    unsigned int size() const { return num; }
    bool empty() const { return num == 0; }
    T& operator[](unsigned int index) { return buff[index]; }
    T& front() { return buff[0]; }
    T& back() { return buff[num - 1]; }

    void reserve(unsigned int newcap) {
        if (newcap <= cap) return;
        T* newBuff = new T[newcap];
        for (unsigned int i = 0; i < num; ++i) {
            newBuff[i] = buff[i];
        }
        delete[] buff;
        buff = newBuff;
        cap = newcap;
    }

    void pushBack(const T& x) {
        if (cap == num) reserve(cap == 0 ? 1 : cap * 2);
        buff[num++] = x;
    }

    void pushFront(const T& x) {
        if (cap == num) reserve(cap == 0 ? 1 : cap * 2);
        for (unsigned int i = num; i > 0; --i) {
            buff[i] = buff[i - 1];
        }
        buff[0] = x;
        ++num;
    }

    void popBack() {
        if (num > 0) --num;
    }

    void insert(unsigned int index, const T& x) {
        if (cap == num) reserve(cap == 0 ? 1 : cap * 2);
        for (unsigned int i = num; i > index; --i) {
            buff[i] = buff[i - 1];
        }
        buff[index] = x;
        ++num;
    }

    Iterator<T> begin() { return Iterator<T>(buff); }
    Iterator<T> end() { return Iterator<T>(buff + num); }
    ReverseIterator<T> rbegin() { return ReverseIterator<T>(buff + num - 1); }
    ReverseIterator<T> rend() { return ReverseIterator<T>(buff - 1); }
};

template<class T>
class Iterator {
private:
    T *current;
public:
    Iterator(T *ptr) : current(ptr) {}
    T& operator*() { return *current; }
    Iterator& operator++() { ++current; return *this; }
    bool operator!=(const Iterator &it) const { return current != it.current; }
    operator T*() const { return current; }
};

template<class T>
class ReverseIterator {
private:
    T *current;
public:
    ReverseIterator(T *ptr) : current(ptr) {}
    T& operator*() { return *current; }
    ReverseIterator& operator++() { --current; return *this; }
    bool operator!=(const ReverseIterator &it) const { return current != it.current; }
    operator T*() const { return current; }
};

int main() {
    /* Vector<int> a;
    a.pushBack(12);
    a.pushBack(13);
    a.pushBack(14);
    a.pushBack(15);
    a.pushBack(16);
    a.popBack();

    for (auto it = a.begin(); it != a.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    a.pushFront(5);
    a.insert(1, 28);

    for (auto z : a) cout << z << " ";
    cout << endl;

    for (auto rit = a.rbegin(); rit != a.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;

    return 0; */
}
