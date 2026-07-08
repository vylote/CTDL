#pragma once
#include "ProductLinkedList.h"

class Store
{
private:
    ProductLinkedList list;

public:
    Store() {}

    // 1. Nhap danh sach mat hang ban dau
    void inputInitialList();

    // 2. In toan bo danh sach mat hang trong cua hang
    void printAll();

    // 3. Nhap hang (tang ton kho hoac tao mat hang moi neu chua co)
    void importGoods();

    // 4. Xuat hang (giam ton kho, kiem tra du so luong)
    void exportGoods();

    // 5. Tim kiem mat hang theo ma
    void searchProduct();

    // 6. In cac mat hang cung mot loai + dem so luong
    void listByCategory();

    // 7. Cap nhat don gia mat hang
    void updatePrice();

    // 8. Xoa mat hang theo ma
    void removeProduct();

    // 9. Tim mat hang co don gia cao nhat
    void showMaxPrice();

    // 10. Tinh tong gia tri hang ton kho
    void showTotalValue();

    // 11. Sap xep danh sach theo don gia (tang/giam)
    void sortList();

    // 12. Menu chuong trinh
    void run();
};