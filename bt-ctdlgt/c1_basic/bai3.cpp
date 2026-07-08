#include <bits/stdc++.h>
using namespace std;

void maxmin(int a, int b, int c, int &max, int &min) {
    int temp1 = b>c?b:c;
    int temp2 = b<=c?b:c;
    max = a>temp1?a:temp1;
    min = a<=temp2?a:temp2;
}

int main() {
    int a, b, c, max, min; cin >> a >> b >> c;
    maxmin(a,b,c,max,min);
    cout << max << " " << min;
}