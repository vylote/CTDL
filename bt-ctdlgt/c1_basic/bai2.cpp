#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; getline(cin, s);
    string res1 = "", res2 = "";
    for (char &c : s) {
        res1 += tolower(c);
        res2 += toupper(c);
    }

    cout << res1 << " " << res2;
}