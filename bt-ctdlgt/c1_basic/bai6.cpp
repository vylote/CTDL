#include <bits/stdc++.h>
using namespace std;

template<class T>
T gcd(T& a, T& b) {
    if (b == 0) 
        return a;
    return gcd(b, a%b);
} 

int main() {
    cout << gcd(-45,-30);
}