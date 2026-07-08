#include "bai7.cpp"

class Triangle{
    private:
        Point a, b, c;
    public:
        Triangle() {}
        Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {}
        void input() {
            a.input(); b.input(); c.input();
        }
        void display() {
            a.display(); b.display(); c.display();
        }
        float Perimeter () {return a.distance(b)+b.distance(c)+c.distance(a);}
        float Area() {
            float halfPerimeter = Perimeter()/2;
            float x1 = a.distance(b);
            float x2 = b.distance(c);
            float x3 = c.distance(a);
            return sqrt(halfPerimeter*(halfPerimeter-x1)*(halfPerimeter-x2)*(halfPerimeter-x3));
        } 
        friend istream& operator>>(istream& is, Triangle& t) {
            is >> t.a >> t.b >> t.c;
            return is;
        }
        friend ostream& operator<<(ostream& os, Triangle& t) {
            os << t.a << " " << t.b << " " << t.c << "\n";
            return os;
        }
};

int main() {
    Triangle a;
    cin >> a; cout << a; cout << a.Area() << "\n" << a.Perimeter();
}