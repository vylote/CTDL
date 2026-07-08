#include <bits/stdc++.h>
using namespace std;

template <class T>
void InsertSort(T *a, int n)  
{
    int i, j;
    for (i = 1; i < n; ++i) {
        j = i-1;
        T t = a[i];
        while(t < a[j] && j >= 0)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = t;
    }
}
int main() 
{
    int a[] = {12, 13, 9, 25, 7, 31, 3, 37, 14, 22, 15};
    int n = sizeof(a)/sizeof(int);
    InsertSort(a, n);
    for (auto z : a) cout << z<<" ";
    return 0;
}