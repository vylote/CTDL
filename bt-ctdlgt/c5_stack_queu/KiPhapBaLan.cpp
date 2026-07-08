#include <bits/stdc++.h>
using namespace std;

template<class T>
class Stack {
    private:
        T* s;
        int t, capacity; //t: luu chi so phan tu thu n-1
    public:
        Stack(int cap=8) : t(-1), capacity(cap) {s = new T[cap];}
        ~Stack() {delete[] s;}
        int size() {return t+1;}
        bool isEmpty() {return t<0;}
        void push(T val) {
            if (t+1 == capacity) {
                capacity *= 2;
                T* tmp = new T[capacity];
                for (int i=0;i<=t;++i) tmp[i]=s[i];
                delete[] s;
                s = tmp;
            }
            s[++t]=val;
        }
        void pop() {
            if (t<0) return;
            --t;
        }
        T top() {return s[t];}
};

int prorityOp(const char &o) {
    if (o == '+' or o == '-') return 1;
    if (o == '/' or o == '*') return 2;
    if (o == '^') return 3;
    return 0;
}

bool isOp(char &c) {
    return c == '+' || c == '-' || c == '*' || c == '/'  || c=='^';
}

int main() {
    // string s = "1*(2+3)-(4*1)";
    string s = "2^3^4";
    Stack<char> OPR, BLE;
    for (char& c:s) {
        if (c == '(')
            OPR.push(c);
        if (isdigit(c))
            BLE.push(c);
        if (c == ')') {
            while (OPR.top() != '(')
            {
                char t = OPR.top(); OPR.pop();
                BLE.push(t);
            }
            OPR.pop();
        }
        if (isOp(c)) {
            if (OPR.isEmpty()) OPR.push(c);
            else {
                while (!OPR.isEmpty() && 
                        OPR.top() != '(' && 
                        prorityOp(OPR.top()) >= prorityOp(c) && c !='^') {
                    char u = OPR.top(); OPR.pop();
                    BLE.push(u);
                }
                OPR.push(c);
            }
        }
    }
    while (!OPR.isEmpty()) {
        char u = OPR.top(); OPR.pop();
        BLE.push(u);
    }

    string res = "";
    while (!BLE.isEmpty()) {
        res += BLE.top();
        BLE.pop();
    }
    reverse(res.begin(), res.end());
    cout << res;
}