#include <bits/stdc++.h>
using namespace std;

template<class T>
T max(T& a, T& b) {
    return a>b?a:b;
}

int main() {
    cout << max(1,2) << "\n";
    cout << max(10.3,-13.5) << "\n";
}