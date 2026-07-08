#pragma once
#include "SLL.h"

void bai3() {
    SLL<int> l;
    cout << "ds l:\n";
    l.input(); 

    auto [even, odd] = l.split();
    cout << "ds chan: ";
    even.print();
    cout << "ds le: ";
    odd.print();
}