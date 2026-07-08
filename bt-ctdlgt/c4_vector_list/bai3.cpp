#include "bai1.cpp"

struct ThiSinh{
    string sdb, hoTen, gioiTinh;
    int namSinh; float diem;
};

istream& operator>>(istream& is, ThiSinh& t) {
    is >> t.sdb >> t.hoTen >> t.namSinh >> t.gioiTinh >> t.diem;
    return is;
}

ostream& operator<<(ostream& os, const ThiSinh& t) {
    os << t.sdb << " " << t.hoTen << " " << t.namSinh 
       << " " << t.gioiTinh << " " << t.diem << "\n";
    return os;
}

class Menu {
    private:
        Vector<ThiSinh> ts;
    public:
        void read(string file) {
            ifstream inFile(file);
            if (!inFile) {
                cout << "khong the mo file " << file << "\n";
                return;
            }
            ThiSinh t;
            while (inFile >> t) {
                ts.pushBack(t);
            }
            inFile.close();
            cout << "doc file thanh cong!\n";
            for (auto it = ts.begin(); it != ts.end(); ++it) {
                cout << *it;
            }
        }

        void write(string file) {
            ofstream outFile(file);
            if (!outFile) {
                cout << "khong the ghi file" << file <<"\n";
                return;
            }
            for (auto it = ts.begin(); it != ts.end(); ++it) {
                outFile << *it;
            }
            outFile.close();
            cout << "ghi thanh cong\n";
        }
        void addTS(ThiSinh &t) {
            ts.pushBack(t);
            cout << "them thanh cong thi sinh vao danh sach\n";
        }
        void xoaThiSinh(string sbd) {
            for (int i = 0;i<ts.size(); ++i) {
                if (ts[i].sdb == sbd) {
                    ts.erase(i);
                    cout << "xoa thanh cong\n";
                    return;
                }
            }
        }
        void print() {
            for(int i =0; i<ts.size(); ++i)
                cout << ts[i] << "\n";
        }
        void app() {
            int n; cin >> n;
            ThiSinh t;
            string sbd;
            switch (n)
            {
            case 1:
                read("bai3.txt");
                break;
            case 2:
                write("bai3.txt");
                break;
            case 3:
                cin >> t;
                addTS(t);
                break;
            case 4:
                cin >> sbd;
                xoaThiSinh(sbd);
                break;
            case 5:
                print();
                break;
            
            default:
                break;
            }
        }
};

int main() {
    Menu m;
    m.app();
}