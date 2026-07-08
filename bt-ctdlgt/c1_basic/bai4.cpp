#include <bits/stdc++.h>
using namespace std;

int MaxMin(int a, int b, int c, bool ismax = true) {
    if (ismax) {
        int temp1 = b>c?b:c;
        return a>temp1?a:temp1;
    } else {
        int temp2 = b<=c?b:c;
        return a<=temp2?a:temp2;
    }
}

int main() {
    int a, b, c; cin >> a >> b >> c;
    int res = false;
    cout << MaxMin(a,b,c,res);
}