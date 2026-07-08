#include "Store.h"
#include <limits>

// ===== 1. Nhap danh sach mat hang ban dau =====
void Store::inputInitialList()
{
    cout << "Nhap so luong mat hang ban dau: ";
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        cout << "-- Mat hang thu " << (i + 1) << " --\n";

        int id;
        cout << "  Ma (id): ";
        cin >> id;
        cin.ignore();

        string name, category;
        cout << "  Ten: ";
        getline(cin, name);
        cout << "  Loai: ";
        getline(cin, category);

        int quantity;
        cout << "  So luong: ";
        cin >> quantity;

        double price;
        cout << "  Don gia: ";
        cin >> price;
        cin.ignore();

        list.addProduct(Product(id, name, category, quantity, price));
    }
    cout << "Da nhap " << n << " mat hang.\n";
}

// ===== 2. In toan bo danh sach mat hang =====
void Store::printAll()
{
    cout << "-- Danh sach mat hang trong cua hang --\n";
    list.print();
}

// ===== 3. Nhap hang =====
void Store::importGoods()
{
    int id;
    cout << "Nhap ma mat hang can nhap: ";
    cin >> id;

    int qty;
    cout << "Nhap so luong can nhap them: ";
    cin >> qty;
    cin.ignore();

    Product *p = list.searchById(id);
    if (p != nullptr)
    {
        // Mat hang da ton tai -> tang so luong ton kho
        p->setQuantity(p->getQuantity() + qty);
        cout << "Da tang ton kho. So luong moi: " << p->getQuantity() << "\n";
    }
    else
    {
        // Mat hang chua ton tai -> nhap them thong tin va them vao danh sach
        cout << "Mat hang chua co trong danh sach, nhap them thong tin moi:\n";
        string name, category;
        cout << "  Ten: ";
        getline(cin, name);
        cout << "  Loai: ";
        getline(cin, category);
        double price;
        cout << "  Don gia: ";
        cin >> price;

        list.addProduct(Product(id, name, category, qty, price));
        cout << "Da them mat hang moi vao danh sach.\n";
    }
}

// ===== 4. Xuat hang =====
void Store::exportGoods()
{
    int id;
    cout << "Nhap ma mat hang can xuat: ";
    cin >> id;

    int qty;
    cout << "Nhap so luong can xuat: ";
    cin >> qty;

    Product *p = list.searchById(id);
    if (p == nullptr)
    {
        cout << "Khong tim thay mat hang co ma " << id << ".\n";
        return;
    }
    if (p->getQuantity() < qty)
    {
        cout << "Khong du so luong de xuat hang (con " << p->getQuantity() << ").\n";
        return;
    }
    p->setQuantity(p->getQuantity() - qty);
    cout << "Da xuat hang. So luong con lai: " << p->getQuantity() << "\n";
}

// ===== 5. Tim kiem mat hang theo ma =====
void Store::searchProduct()
{
    int id;
    cout << "Nhap ma mat hang can tim: ";
    cin >> id;

    Product *p = list.searchById(id);
    if (p == nullptr)
        cout << "Khong tim thay mat hang co ma " << id << ".\n";
    else
        cout << *p << "\n";
}

// ===== 6. In cac mat hang cung loai + dem so luong =====
void Store::listByCategory()
{
    cin.ignore();
    cout << "Nhap loai hang can liet ke: ";
    string category;
    getline(cin, category);

    int count = 0;
    for (Iterator it = list.begin(); it != list.end(); ++it)
    {
        if (it->getCategory() == category)
        {
            cout << *it << "\n";
            count++;
        }
    }
    cout << "So luong mat hang thuoc loai \"" << category << "\": " << count << "\n";
}

// ===== 7. Cap nhat don gia mat hang =====
void Store::updatePrice()
{
    int id;
    cout << "Nhap ma mat hang can cap nhat gia: ";
    cin >> id;

    double price;
    cout << "Nhap don gia moi: ";
    cin >> price;

    if (list.updatePriceById(id, price))
        cout << "Cap nhat thanh cong.\n";
    else
        cout << "Khong tim thay mat hang co ma " << id << ".\n";
}

// ===== 8. Xoa mat hang theo ma =====
void Store::removeProduct()
{
    int id;
    cout << "Nhap ma mat hang can xoa: ";
    cin >> id;

    if (list.removeById(id))
        cout << "Da xoa mat hang co ma " << id << ".\n";
    else
        cout << "Khong tim thay mat hang co ma " << id << ".\n";
}

// ===== 9. Tim mat hang co don gia cao nhat =====
void Store::showMaxPrice()
{
    Product *p = list.findMaxPrice();
    if (p == nullptr)
        cout << "Danh sach dang rong.\n";
    else
        cout << "Mat hang co don gia cao nhat: " << *p << "\n";
}

// ===== 10. Tinh tong gia tri hang ton kho =====
void Store::showTotalValue()
{
    double total = list.totalValueStockQuantity();
    cout << "Tong gia tri hang ton kho: "
         << fixed << setprecision(0) << total
         << defaultfloat << "\n"; // defaultfloat: tra dinh dang ve mac dinh sau khi in
}

// ===== 11. Sap xep danh sach theo don gia =====
void Store::sortList()
{
    cout << "Chon kieu sap xep:\n  1. Tang dan\n  2. Giam dan\n";
    cout << "Lua chon: ";
    int choice;
    cin >> choice;

    list.sortByPrice(choice != 2);
    cout << "Da sap xep xong.\n";
}

// ===== 12. Menu chuong trinh =====
void Store::run()
{
    int choice;
    do
    {
        cout << "\n========== MENU CUA HANG ==========\n";
        cout << "1. Nhap danh sach mat hang ban dau\n";
        cout << "2. In toan bo danh sach mat hang\n";
        cout << "3. Nhap hang\n";
        cout << "4. Xuat hang\n";
        cout << "5. Tim kiem mat hang theo ma\n";
        cout << "6. In mat hang theo loai + dem so luong\n";
        cout << "7. Cap nhat don gia mat hang\n";
        cout << "8. Xoa mat hang theo ma\n";
        cout << "9. Tim mat hang co don gia cao nhat\n";
        cout << "10. Tinh tong gia tri hang ton kho\n";
        cout << "11. Sap xep danh sach theo don gia\n";
        cout << "0. Thoat\n";
        cout << "Chon chuc nang: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore();
            cout << "Lua chon khong hop le.\n";
            continue;
        }

        switch (choice)
        {
        case 1: inputInitialList(); break;
        case 2: printAll(); break;
        case 3: importGoods(); break;
        case 4: exportGoods(); break;
        case 5: searchProduct(); break;
        case 6: listByCategory(); break;
        case 7: updatePrice(); break;
        case 8: removeProduct(); break;
        case 9: showMaxPrice(); break;
        case 10: showTotalValue(); break;
        case 11: sortList(); break;
        case 0: cout << "Tam biet!\n"; break;
        default: cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}