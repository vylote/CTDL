#include <bits/stdc++.h>
using namespace std;

template <class T>
void Heapify(T* a, int i, int n) {
    int kt = 0;
    int max;
    int j = i;
    while(kt == 0 && j <=n/2) 
    {
        if (n == 2*j) max = 2*j;
        else {
            if(a[2*j] <= a[2*j+1]) max = 2*j+1;
            else max = 2*j;
        }
        if (a[j] < a[max]) {
            swap(a[j],a[max]);
            j = max;
        }
        else kt = 1;
    }
}
template <class T>
void HeapSort(T *a,int n) {
    int i;
    for (i = (n-1)/2; i >=0; --i) 
        Heapify(a, i, n-1);

    for (i = n-1; i >= 1; --i) {
        swap(a[0], a[i]); 
        Heapify(a, 0, i-1);
    }
}

int main() {
    int a[] = {12, 13, 9, 25, 7, 31, 3, 37, 14, 22, 15};
    int n = sizeof(a)/sizeof(int);
    HeapSort(a, 11);
    for (auto z : a) cout << z << ' ';

    return 0;
}