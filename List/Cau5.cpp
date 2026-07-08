// bai5.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "DLL.h"
using namespace std;

struct SinhVien {
    string maSV;
    string hoTen;
    int namSinh;
    string gioiTinh;
    string queQuan;
};

// -------- Tìm node theo mã SV --------
Node<SinhVien>* timTheoMa(List<SinhVien>& ds, const string& ma) {
    for (auto it = ds.begin(); it != ds.end(); ++it)
        if (it->maSV == ma) return it.node();  // ← dùng .node()
    return 0;
}

// -------- In 1 sinh viên --------
void inSinhVien(const SinhVien& sv) {
    cout << "Ma: "        << sv.maSV
         << " | Ho ten: " << sv.hoTen
         << " | Nam sinh: "<< sv.namSinh
         << " | Gioi tinh: "<< sv.gioiTinh
         << " | Que quan: "<< sv.queQuan
         << "\n";
}

// -------- 1. Đọc file --------
void docFile(List<SinhVien>& ds, const string& tenFile) {
    ifstream f(tenFile);
    if (!f) { cout << "Khong mo duoc file!\n"; return; }

    // Xóa danh sách cũ
    while (!ds.empty()) ds.remove(ds.begin().node());

    int count = 0;
    string line;
    while (getline(f, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        istringstream ss(line);
        SinhVien sv;
        string namSinh;
        getline(ss, sv.maSV,      ',');
        getline(ss, sv.hoTen,     ',');
        getline(ss, namSinh,      ',');  sv.namSinh = stoi(namSinh);
        getline(ss, sv.gioiTinh,  ',');
        getline(ss, sv.queQuan);
        ds.push_back(new Node<SinhVien>(sv));
        count++;
    }
    f.close();
    cout << "Da doc duoc " << count << " sinh vien:\n";
    cout << "--- Danh sach sinh vien ---\n";
    for (auto it = ds.begin(); it != ds.end(); ++it)
        inSinhVien(*it);
}

// -------- 2. Ghi file --------
void ghiFile(List<SinhVien>& ds, const string& tenFile) {
    ofstream f(tenFile);
    if (!f) { cout << "Khong mo duoc file!\n"; return; }
    for (auto it = ds.begin(); it != ds.end(); ++it)
        f << it->maSV     << ","
          << it->hoTen    << ","
          << it->namSinh  << ","
          << it->gioiTinh << ","
          << it->queQuan  << "\n";
    f.close();
    cout << "Da ghi ra file.\n";
}

// -------- 3. Thêm sinh viên --------
void themSinhVien(List<SinhVien>& ds) {
    SinhVien sv;
    cout << "Nhap ma SV: ";     cin.ignore(); getline(cin, sv.maSV);
    cout << "Nhap ho ten: ";    getline(cin, sv.hoTen);
    cout << "Nhap nam sinh: ";  cin >> sv.namSinh;
    cin.ignore();
    cout << "Nhap gioi tinh: "; getline(cin, sv.gioiTinh);
    cout << "Nhap que quan: ";  getline(cin, sv.queQuan);
    ds.push_back(new Node<SinhVien>(sv));
    cout << "Da them sinh vien.\n";
}

// -------- 4. Xóa theo mã --------
void xoaSinhVien(List<SinhVien>& ds) {
    string ma;
    cout << "Nhap ma SV can xoa: "; cin >> ma;
    Node<SinhVien>* p = timTheoMa(ds, ma);
    if (!p) { cout << "Khong tim thay!\n"; return; }
    ds.remove(p);
    cout << "Da xoa.\n";
}

// -------- 5. Cập nhật theo mã --------
void capNhatSinhVien(List<SinhVien>& ds) {
    string ma;
    cout << "Nhap ma SV can cap nhat: "; cin >> ma;
    Node<SinhVien>* p = timTheoMa(ds, ma);
    if (!p) { cout << "Khong tim thay!\n"; return; }
    SinhVien sv = p->getData();
    cout << "Thong tin hien tai: "; inSinhVien(sv);
    cin.ignore();
    cout << "Ho ten moi: ";    getline(cin, sv.hoTen);
    cout << "Nam sinh moi: ";  cin >> sv.namSinh; cin.ignore();
    cout << "Gioi tinh moi: "; getline(cin, sv.gioiTinh);
    cout << "Que quan moi: ";  getline(cin, sv.queQuan);
    p->setData(sv);
    cout << "Da cap nhat.\n";
}

// -------- 6. Hiển thị theo mã --------
void hienThiSinhVien(List<SinhVien>& ds) {
    string ma;
    cout << "Nhap ma SV: "; cin >> ma;
    Node<SinhVien>* p = timTheoMa(ds, ma);
    if (!p) { cout << "Khong tim thay!\n"; return; }
    inSinhVien(p->getData());
}

// -------- 7. In toàn bộ --------
void inDanhSach(List<SinhVien>& ds) {
    if (ds.empty()) { cout << "Danh sach trong.\n"; return; }
    cout << "--- Danh sach sinh vien ---\n";
    for (auto it = ds.begin(); it != ds.end(); ++it)
        inSinhVien(*it);
}

// -------- Menu --------
int main() {
    List<SinhVien> ds;
    string tenFile = "sinhvien.csv";
    int choice;

    do {
        cout << "\n===== QUAN LY SINH VIEN =====\n"
             << "1. Doc danh sach tu file\n"
             << "2. Ghi danh sach ra file\n"
             << "3. Them sinh vien\n"
             << "4. Xoa sinh vien theo ma\n"
             << "5. Cap nhat sinh vien theo ma\n"
             << "6. Hien thi sinh vien theo ma\n"
             << "7. In toan bo danh sach\n"
             << "0. Thoat\n"
             << "Chon: ";
        cin >> choice;

        switch (choice) {
            case 1: docFile(ds, tenFile);        break;
            case 2: ghiFile(ds, tenFile);        break;
            case 3: themSinhVien(ds);            break;
            case 4: xoaSinhVien(ds);             break;
            case 5: capNhatSinhVien(ds);         break;
            case 6: hienThiSinhVien(ds);         break;
            case 7: inDanhSach(ds);              break;
            case 0: cout << "Thoat.\n";          break;
            default: cout << "Khong hop le.\n";
        }
    } while (choice != 0);

    return 0;
}