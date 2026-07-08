// chia de tri
#include <bits/stdc++.h>
using namespace std;

template <class T>
int Partition(T* a, int left, int right) {
    int x = a[left];
    int i = left+1;
    int j = right;
    do {
        while (i <= j && a[i] <= x) i++;
        while (i <= j && a[j] > x) j--;
        if (i < j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }while(i <= j);
    swap(a[left], a[j]);
    return j;
}
template <class T>
void quickSort(T* a, int left, int right)
{
    int k;
    if (left < right) 
    {
        k = Partition(a,left, right);
        quickSort(a, left, k-1);
        quickSort(a, k+1, right);
    }
}

int main() {
    int a[] = {12, 13, 9, 25, 7, 31, 3, 37, 14, 22, 15};
    int n = sizeof(a)/sizeof(int);
    quickSort(a,0,10);
    for (auto z : a) cout << z << ' ';

    return 0;
}