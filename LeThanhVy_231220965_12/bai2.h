#pragma once
#include "SLL.h"

void bai2() {
    SLL<int> a, b;
    cout << "ds a:\n";
    a.input(); 
    cout << "ds b:\n";
    b.input();
    SLL<int> res = a.merge(b);
    cout << "ds sau tron: ";
    res.print();
}