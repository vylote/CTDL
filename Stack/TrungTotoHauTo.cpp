#include <bits/stdc++.h>
using namespace std;
#include "Vector.h"
#include "ArrayStack.h"

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^')               return 3;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/'  || c=='^';
}

// Chuyen trung to -> hau to
string convert(string input) {
    int z = input.length();
    Vector<char> output;
    ArrayStack<char> S;

    for (int i = 0; i < z; i++) {
        char c = input[i];

        if (isalnum(c)) {
            output.push_back(c);
        }
        else if (isOperator(c)) {
            while (!S.isEmpty()
                && S.top() != '('
                && (c == '^' ? priority(S.top()) > priority(c)   // right-associative
                     : priority(S.top()) >= priority(c))) // left-associative
            {
                char o; S.pop(o);
                output.push_back(o);
            }
            S.push(c);
        }
        else if (c == '(') {
            S.push(c);
        }
        else if (c == ')') {
            while (!S.isEmpty() && S.top() != '(') {
                char o; S.pop(o);
                output.push_back(o);
            }
            char dummy; S.pop(dummy); // bo '(' di
        }
    }

    while (!S.isEmpty()) {
        char o; S.pop(o);
        output.push_back(o);
    }

    string res = "";
    for (int j = 0; j < output.size(); j++) res += output[j];
    return res;
}

// Tinh gia tri bieu thuc hau to (chi ho tro so 1 chu so)
int calculate(string postfix) {
    ArrayStack<int> S;

    for (int i = 0; i < (int)postfix.size(); i++) {
        char c = postfix[i];

        if (isdigit(c)) {
            S.push(c - '0');
        }
        else if (isOperator(c)) {
            int a; S.pop(a); // toan hang PHAI
            int b; S.pop(b); // toan hang TRAI
            int result;
            if      (c == '+') result = b + a;
            else if (c == '-') result = b - a;
            else if (c == '*') result = b * a;
            else if (c == '^') result = pow(b, a);
            else               result = b / a;
            S.push(result);
        }
    }

    int res; S.pop(res);
    return res;
}

int main() {
    cout << "=== convert ===" << endl;
    cout << convert("a*(b+c)-(d*a)") << endl; // abc+*da*-
    cout << convert("a+b*c")         << endl; // abc*+
    cout << convert("(a+b)*(c-d)")   << endl; // ab+cd-*

    cout << "\n=== calculate ===" << endl;
    string p1 = convert("3*(2+4)");
    cout << "3*(2+4)      hau to=" << p1 << "  ket qua=" << calculate(p1) << endl;

    string p2 = convert("5+3*2");
    cout << "5+3*2        hau to=" << p2 << "  ket qua=" << calculate(p2) << endl;

    string p3 = convert("(6+2)*(5-3)");
    cout << "(6+2)*(5-3)  hau to=" << p3 << "  ket qua=" << calculate(p3) << endl;

    string p4 = convert("8-4/2");
    cout << "8-4/2        hau to=" << p4 << "  ket qua=" << calculate(p4) << endl;

    return 0;
}