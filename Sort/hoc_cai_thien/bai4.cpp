#include <bits/stdc++.h>
using namespace std;

template <class T>
void Swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// ====== Struct thí sinh ======
struct ThiSinh {
    string SBD;
    string HoTen;
    float DiemToan, DiemLy, DiemHoa;

    float TongDiem() const {
        return DiemToan + DiemLy + DiemHoa;
    }
};

// Dùng cho InsertSort, SelectSort (chúng so sánh trực tiếp bằng operator<)
bool operator<(const ThiSinh &a, const ThiSinh &b) {
    return a.TongDiem() < b.TongDiem();
}
bool operator<=(const ThiSinh &a, const ThiSinh &b) {
    return a.TongDiem() <= b.TongDiem();
}
bool operator>(const ThiSinh &a, const ThiSinh &b) {
    return a.TongDiem() > b.TongDiem();
}

// Dùng cho BubbleSort (truyền con trỏ hàm so sánh)
bool tang(ThiSinh& a, ThiSinh& b) { return a.TongDiem() <= b.TongDiem(); }
bool giam(ThiSinh& a, ThiSinh& b) { return b.TongDiem() > a.TongDiem(); }

// ====== Các thuật toán sắp xếp (tổng quát bằng template) ======
template <class T>
void BubbleSort(T *a, int n, bool (*comp)(T&, T&)) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j)
            if (comp(a[j], a[j + 1])) Swap(a[j], a[j + 1]);
}

template <class T>
void InsertSort(T *a, int n) {
    for (int i = 1; i < n; ++i) {
        T t = a[i];
        int j = i - 1;
        while (j >= 0 && t < a[j]) {   // sửa thứ tự điều kiện
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = t;
    }
}

template <class T>
void SelectSort(T *a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int idxMin = i;
        for (int j = i + 1; j < n; ++j)
            if (a[j] < a[idxMin]) idxMin = j;
        if (idxMin != i) Swap(a[idxMin], a[i]);
    }
}

template <class T>
int Partition(T* a, int left, int right) {
    T x = a[left];
    int i = left+1;
    int j = right;
    do {
        while (i <= j && a[i] <= x) i++;
        while (i <= j && a[j] > x) j--;
        if (i < j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }while(i <= j);
    swap(a[left], a[j]);
    return j;
}
template <class T>
void QuickSort(T* a, int left, int right)
{
    int k;
    if (left < right) 
    {
        k = Partition(a,left, right);
        QuickSort(a, left, k-1);
        QuickSort(a, k+1, right);
    }
}

template <class T>
void Merge(T *a, int left, int mid, int right) {
    int i = left;
    int j = mid+1;
    int k = 0;
    int n = right-left+1;
    T *b = new T[n];

    while(i < mid+1 && j < right+1)
    {
        if (a[i] < a[j])
        {
            b[k] = a[i];
            k++; i++;
        }
        else 
        {
            b[k] = a[j];
            k++; j++;
        }
    }

    while(i < mid+1) 
    {   
        b[k] = a[i];
        k++; i++;
    }
    while(j < right+1)
    {
        b[k] = a[j];
        k++; j++;
    }
    i = left;
    for (k = 0; k < n; k++) 
    {
        a[i] = b[k];
        i++;
    }
    delete[] b;
}

template <class T>
void MergeSort(T* a, int left, int right) {
    if (left < right) 
    {
        int mid = (left + right)/2;
        MergeSort(a,left, mid);
        MergeSort(a,mid+1, right);
        Merge(a, left, mid, right);
    }
}

// ====== In danh sách ======
void Xuat(ThiSinh *a, int n) {
    cout << left << setw(8) << "SBD" << setw(20) << "Ho ten"
         << setw(8) << "Toan" << setw(8) << "Ly" << setw(8) << "Hoa"
         << setw(8) << "Tong" << '\n';
    for (int i = 0; i < n; ++i)
        cout << left << setw(8) << a[i].SBD << setw(20) << a[i].HoTen
             << setw(8) << a[i].DiemToan << setw(8) << a[i].DiemLy
             << setw(8) << a[i].DiemHoa << setw(8) << a[i].TongDiem() << '\n';
    cout << '\n';
}

int main() {
    ThiSinh ds[] = {
        {"001", "Nguyen Van A", 8.0, 7.5, 6.0},
        {"002", "Tran Thi B",   9.0, 8.5, 9.5},
        {"003", "Le Van C",     5.0, 6.0, 7.0},
        {"004", "Pham Thi D",   7.0, 7.0, 7.0},
        {"005", "Hoang Van E", 10.0, 9.0, 8.5},
    };
    int n = sizeof(ds) / sizeof(ThiSinh);

    cout << "Danh sach ban dau:\n";
    Xuat(ds, n);

    // Tạo 3 bản sao để test riêng từng thuật toán
    ThiSinh ds1[5], ds2[5], ds3[5], ds4[5], ds5[5];
    copy(ds, ds + n, ds1);
    copy(ds, ds + n, ds2);
    copy(ds, ds + n, ds3);
    copy(ds, ds + n, ds4);
    copy(ds, ds + n, ds5);

    BubbleSort(ds1, n, giam);   // sắp xếp giảm dần theo tổng điểm
    cout << "Sau BubbleSort (giam dan theo tong diem):\n";
    Xuat(ds1, n);

    InsertSort(ds2, n);         // mặc định tăng dần (theo operator<)
    cout << "Sau InsertSort (tang dan theo tong diem):\n";
    Xuat(ds2, n);

    SelectSort(ds3, n);         // mặc định tăng dần (theo operator<)
    cout << "Sau SelectSort (tang dan theo tong diem):\n";
    Xuat(ds3, n);

    QuickSort(ds4, 0, n-1);
    cout << "Sau QuickSort (tang dan theo tong diem):\n";
    Xuat(ds4, n);

    MergeSort(ds5, 0, n-1);
    cout << "Sau MergeSort (tang dan theo tong diem):\n";
    Xuat(ds5, n);

    return 0;
}