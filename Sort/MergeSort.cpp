#include <bits/stdc++.h>
using namespace std;

template <class T>
void Merge(T *a, int left, int mid, int right) {
    int i = left;
    int j = mid+1;
    int k = 0;
    int n = right-left+1;
    T *b = new T[n];

    while(i < mid+1 && j < right+1)
    {
        if (a[i] < a[j])
        {
            b[k] = a[i];
            k++; i++;
        }
        else 
        {
            b[k] = a[j];
            k++; j++;
        }
    }

    while(i < mid+1) 
    {   
        b[k] = a[i];
        k++; i++;
    }
    while(j < right+1)
    {
        b[k] = a[j];
        k++; j++;
    }
    i = left;
    for (k = 0; k < n; k++) 
    {
        a[i] = b[k];
        i++;
    }
    delete[] b;
}

template <class T>
void MergeSort(T* a, int left, int right) {
    if (left < right) 
    {
        int mid = (left + right)/2;
        MergeSort(a,left, mid);
        MergeSort(a,mid+1, right);
        Merge(a, left, mid, right);
    }
}

int main() 
{
    int a[] = {12, 13, 9, 25, 7, 31, 3, 37, 14, 22, 15};
    int n = sizeof(a)/sizeof(int);
    /* Merge(a, 0, 5, 10);
    for (auto z : a) cout << z << " "; */
    cout << endl;
    MergeSort(a, 0, 10);
    for (auto z : a) cout << z << " ";
    return 0;
}