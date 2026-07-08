#include <bits/stdc++.h>
using namespace std;

template <class T>
void SelectSort(T* a, int n) {
    for (int i = 0; i < n-1; ++i) 
    {
        int min = i;
        for (int j = i+1; j < n; ++j) 
        {
            if (a[j] < a[min]) min = j;
        }
        if (min != i) {
            swap(a[min], a[i]);
        }
    }
}

int main() 
{
    int a[] = {12, 13, 9, 25, 7, 31, 3, 37, 14, 22, 15};
    int n = sizeof(a)/sizeof(int);
    SelectSort(a,n);
    for (auto z : a) cout << z  <<" ";
   return 0;
}