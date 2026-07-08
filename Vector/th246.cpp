/*
    BAI TAP: QUAN LY NHAN VIEN
    - Su dung class Employee de bieu dien 1 nhan vien
    - Su dung Vector<Employee> (class Vector tu xay dung) de luu danh sach
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "Vector.h"

using namespace std;

// ========================================================
// CLASS EMPLOYEE
// ========================================================
class Employee {
public:
    int id;              // Ma nhan vien
    string name;         // Ho ten
    int age;             // Tuoi
    string position;     // Chuc vu
    string department;   // Phong ban
    double salary;       // Muc luong co ban

    Employee() : id(0), age(0), salary(0) {}

    Employee(int _id, string _name, int _age, string _position,
              string _department, double _salary)
        : id(_id), name(_name), age(_age), position(_position),
          department(_department), salary(_salary) {}

    // Nhap thong tin 1 nhan vien tu ban phim
    void input() {
        cout << "  Ma nhan vien      : ";
        cin >> id;
        cout << "  Ho ten            : ";
        cin.ignore();
        getline(cin, name);
        cout << "  Tuoi              : ";
        cin >> age;
        cout << "  Chuc vu           : ";
        cin.ignore();
        getline(cin, position);
        cout << "  Phong ban         : ";
        getline(cin, department);
        cout << "  Luong co ban      : ";
        cin >> salary;
    }

    // In thong tin 1 nhan vien (1 dong)
    void print() const {
        cout << left  << setw(6)  << id
             << left  << setw(20) << name
             << left  << setw(6)  << age
             << left  << setw(15) << position
             << left  << setw(15) << department
             << right << setw(12) << fixed << setprecision(0) << salary
             << "\n";
    }

    // In tieu de bang
    static void printHeader() {
        cout << left  << setw(6)  << "Ma"
             << left  << setw(20) << "Ho ten"
             << left  << setw(6)  << "Tuoi"
             << left  << setw(15) << "Chuc vu"
             << left  << setw(15) << "Phong ban"
             << right << setw(12) << "Luong"
             << "\n";
        cout << string(74, '-') << "\n";
    }
};

// ========================================================
// CAC HAM XU LY TREN Vector<Employee>
// ========================================================

// (1) Nhap danh sach nhan vien
void inputEmployeeList(Vector<Employee> &list) {
    int n;
    cout << "Nhap so luong nhan vien can them: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "\n--- Nhap thong tin nhan vien thu " << (i + 1) << " ---\n";
        Employee e;
        e.input();
        list.push_back(e);
    }
}

// (1) In danh sach nhan vien
void printEmployeeList(Vector<Employee> &list) {
    if (list.size() == 0) {
        cout << "Danh sach nhan vien dang rong!\n";
        return;
    }
    Employee::printHeader();
    for (int i = 0; i < list.size(); i++) {
        list[i].print();
    }
}

// (2) Sap xep danh sach theo luong (ascending = true: tang dan, false: giam dan)
void sortBySalary(Vector<Employee> &list, bool ascending) {
    int n = list.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            bool needSwap = ascending
                ? (list[j].salary > list[j + 1].salary)
                : (list[j].salary < list[j + 1].salary);
            if (needSwap) {
                Employee temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

// (3) In danh sach nhan vien trong 1 phong ban, tra ve so luong tim duoc
int printByDepartment(Vector<Employee> &list, const string &dept) {
    int count = 0;
    bool foundHeader = false;
    for (int i = 0; i < list.size(); i++) {
        if (list[i].department == dept) {
            if (!foundHeader) {
                Employee::printHeader();
                foundHeader = true;
            }
            list[i].print();
            count++;
        }
    }
    return count;
}

// Tim chi so nhan vien theo ma, tra ve -1 neu khong tim thay
int findEmployeeById(Vector<Employee> &list, int id) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i].id == id) return i;
    }
    return -1;
}

// (4) Tim kiem nhan vien theo ma va in ket qua
void searchEmployeeById(Vector<Employee> &list) {
    int id;
    cout << "Nhap ma nhan vien can tim: ";
    cin >> id;
    int idx = findEmployeeById(list, id);
    if (idx == -1) {
        cout << "Khong tim thay nhan vien co ma " << id << "!\n";
    } else {
        cout << "Tim thay nhan vien:\n";
        Employee::printHeader();
        list[idx].print();
    }
}

// (5) Cap nhat luong nhan vien theo ma
void updateSalary(Vector<Employee> &list) {
    int id;
    cout << "Nhap ma nhan vien can cap nhat luong: ";
    cin >> id;
    int idx = findEmployeeById(list, id);
    if (idx == -1) {
        cout << "Khong tim thay nhan vien co ma " << id << "!\n";
        return;
    }
    cout << "Thong tin hien tai:\n";
    Employee::printHeader();
    list[idx].print();

    double newSalary;
    cout << "Nhap muc luong moi: ";
    cin >> newSalary;
    list[idx].salary = newSalary;
    cout << "Cap nhat luong thanh cong!\n";
}

// (6) Xoa nhan vien theo ma
void deleteEmployee(Vector<Employee> &list) {
    int id;
    cout << "Nhap ma nhan vien can xoa: ";
    cin >> id;
    int idx = findEmployeeById(list, id);
    if (idx == -1) {
        cout << "Khong tim thay nhan vien co ma " << id << "!\n";
        return;
    }
    cout << "Da xoa nhan vien: " << list[idx].name << " (ma " << id << ")\n";
    list.erase(idx);
}

// (7) Tim nhan vien co luong cao nhat
void findMaxSalary(Vector<Employee> &list) {
    if (list.size() == 0) {
        cout << "Danh sach nhan vien dang rong!\n";
        return;
    }
    int maxIdx = 0;
    for (int i = 1; i < list.size(); i++) {
        if (list[i].salary > list[maxIdx].salary) maxIdx = i;
    }
    cout << "Nhan vien co luong cao nhat:\n";
    Employee::printHeader();
    list[maxIdx].print();
}

// (8) Tinh tong quy luong cong ty
double totalSalary(Vector<Employee> &list) {
    double total = 0;
    for (int i = 0; i < list.size(); i++) {
        total += list[i].salary;
    }
    return total;
}

// ========================================================
// MENU CHINH
// ========================================================
void showMenu() {
    cout << "\n================= QUAN LY NHAN VIEN =================\n";
    cout << " 1. Nhap danh sach nhan vien\n";
    cout << " 2. In danh sach nhan vien\n";
    cout << " 3. Sap xep va in danh sach theo luong\n";
    cout << " 4. In danh sach nhan vien theo phong ban (+ dem so luong)\n";
    cout << " 5. Tim kiem nhan vien theo ma\n";
    cout << " 6. Cap nhat luong nhan vien\n";
    cout << " 7. Xoa nhan vien theo ma\n";
    cout << " 8. Tim nhan vien co luong cao nhat\n";
    cout << " 9. Tinh tong quy luong cong ty\n";
    cout << " 0. Thoat\n";
    cout << "=======================================================\n";
    cout << "Lua chon cua ban: ";
}

int main() {
    Vector<Employee> employees;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                inputEmployeeList(employees);
                break;

            case 2:
                cout << "\n--- DANH SACH NHAN VIEN ---\n";
                printEmployeeList(employees);
                break;

            case 3: {
                int sc;
                cout << "Sap xep theo luong (1: tang dan, 2: giam dan): ";
                cin >> sc;
                sortBySalary(employees, sc == 1);
                cout << "\n--- DANH SACH SAU KHI SAP XEP THEO LUONG ---\n";
                printEmployeeList(employees);
                break;
            }

            case 4: {
                cin.ignore();
                string dept;
                cout << "Nhap ten phong ban can xem: ";
                getline(cin, dept);
                cout << "\n--- NHAN VIEN PHONG \"" << dept << "\" ---\n";
                int count = printByDepartment(employees, dept);
                cout << "=> So nhan vien trong phong \"" << dept << "\": " << count << "\n";
                break;
            }

            case 5:
                searchEmployeeById(employees);
                break;

            case 6:
                updateSalary(employees);
                break;

            case 7:
                deleteEmployee(employees);
                break;

            case 8:
                findMaxSalary(employees);
                break;

            case 9:
                cout << fixed << setprecision(0);
                cout << "Tong quy luong cong ty: " << totalSalary(employees) << "\n";
                break;

            case 0:
                cout << "Tam biet!\n";
                break;

            default:
                cout << "Lua chon khong hop le, vui long chon lai!\n";
        }

    } while (choice != 0);

    return 0;
}