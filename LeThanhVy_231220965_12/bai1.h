#pragma once
#include "SLL.h"

void bai1() {
    SLL<int> list;
    cout << "n: ";
    int n, val; cin >> n;
    cout << n << " phan tu: ";
    while (n--) {
        cin >> val;
        list.insertOrder(val);
    }
    cout << "ds: ";
    list.print();
}