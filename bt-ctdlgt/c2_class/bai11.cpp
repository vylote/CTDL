#include <bits/stdc++.h>
using namespace std;

template<class T>
class Vector{
    private:
        int n;
        T* a;
    public:
        int getSize() const {return n;}
        T& getVal(int i) {return a[i];}
        const T& getVal(int i) const {return a[i];}
        Vector(int n) : n(n) {a = new T[n];}
        ~Vector() {delete[] a; }
        friend istream& operator>>(istream& is, Vector& v) {
            int size = v.getSize();
            for (int i=0;i<size;++i) {
                T val; is >> val;
                v.getVal(i) = val;
            }
            return is;
        }
        friend ostream& operator<<(ostream &os, const Vector& v) {
            int i, size = v.getSize();
            os << "(";
            for (i=0;i<size-1;++i) 
                os << v.getVal(i) << ",";
            os << v.getVal(i) << ")\n";
            return os;
        }
        Vector operator+(Vector& b) {
            if (this->getSize() != b.getSize()) 
                throw std::invalid_argument("Kich thuoc khong khop");
            int size = getSize(); 
            Vector res(size);
            for (int i = 0; i < size; ++i)
                res.getVal(i) = getVal(i)+b.getVal(i);
            return res;
        }
        Vector operator-(Vector& b) {
            if (this->getSize() != b.getSize()) 
                throw std::invalid_argument("Kich thuoc khong khop");
            int size = getSize(); 
            Vector res(size);
            for (int i = 0; i < size; ++i)
                res.getVal(i) = getVal(i)-b.getVal(i);
            return res;
        }

        Vector operator-() {
            int size = getSize(); 
            Vector res(size);
            for (int i = 0; i < size; ++i)
                res.getVal(i) = -getVal(i);
            return res;
        }

        Vector& operator=(const Vector &b) {
            if (this->getSize() != b.getSize()) 
                throw std::invalid_argument("Kich thuoc khong khop");
            int size = getSize(); 
            
            for (int i = 0; i < size; ++i)
                this->getVal(i) = b.getVal(i);
            return *this;
        }
        T operator*(Vector& b) {
            if (this->getSize() != b.getSize()) 
                throw std::invalid_argument("Kich thuoc khong khop");
            int size = getSize(); 
            T res = T();   
            for (int i = 0; i < size; ++i)
                res += getVal(i)*b.getVal(i);
            return res;
        }
};

int main() {
    int n; cin >> n;
    Vector<int> a(n); cin >> a;
    cout << a;
    Vector<int> b(n); cin >> b;
    cout << b;
    cout << a+b;
    Vector<int> c(n);
    c = a+b;
    cout << c;
    c = a-b;
    cout << c;
    cout << -a;
    c = -a;
    cout << c;
    cout << a*b << "\n";
    cout << (a+b)+c;
    int k = a*b;
    cout << k << "\n";
    cout << (a+b)*c;
}