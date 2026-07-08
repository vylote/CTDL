#include <bits/stdc++.h>
using namespace std;

template <class T>
void Swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
template<class T>
bool tang(T a, T b) {
    return a > b;
}

template<class T>
bool giam(T a, T b) {
    return b > a;
}

template <class T>
void BubbleSort(T *a, int n,bool (*comp)(T,T)) {
    int i, j;
    for (i = 0; i < n-1; ++i) {
        for (j = 0; j < n-1-i; ++j) {
            if (comp(a[j], a[j+1])) Swap(a[j], a[j+1]);
        }
    }
}
template <class T>
void BubbleSort2(T *a, int n,bool (*comp)(T,T)) {
    int i, j;
    for (i = 0; i < n-1; ++i) {
        for (j = n-1; j > i; --j) {
            if (comp(a[j], a[j-1])) Swap(a[j], a[j-1]);
        }
    }
}

int main() {
    int a[] = {5, 1, 4, 2, 8, 9};
    int size = 6;
    BubbleSort(a, size, tang);
    for (auto z : a) cout << z << ' ';
    cout << endl;
    BubbleSort2(a, size, tang);
    for (auto z : a) cout << z << ' ';
}
