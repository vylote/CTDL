#include <bits/stdc++.h>
using namespace std;

class Point {
    private:
        float x, y;
    public:
        Point() : x(0.0), y(0.0) {}
        Point(float x, float y) : x(x), y(y) {}
        void input() {
            cin >> x >> y;
        }
        void display() {
            cout << "(" <<x <<","<<y <<")" << "\n";
        }
        float distance(Point d) {
            return sqrt(pow(getX()-d.getX(),2)+pow(getY()-d.getY(), 2));
        }
        float getX() {return x;}
        float getY() {return y;}
        void setX(float x) {this->x = x;} 
        void setY(float y) {this->y = y;} 
        friend ostream& operator<<(ostream& os, Point& p) {
            os << "(" << p.getX() << "," << p.getY() << ")";
            return os;
        }
        friend istream& operator>>(istream &is, Point& p) {
            is >> p.x >> p.y;
            return is;
        }
};

// int main() {
//     Point a, b;
//     cin >> a >> b;
//     cout << setprecision(4) << a.distance(b);
// }