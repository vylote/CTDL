#include <iostream>
#include <queue>
using namespace std;

class queueApp {
    queue<int> q;
    int size;
    public:
        queueApp(int size) : size(size) {}
        void enQueue(int num) {
            if (q.size() < size) {
                q.push(num);
            }
            else {
                cout << "a queue has been full";
            }
        }
        void reserve() {
            if (q.size() == size) {
                size = size*2+2;
                queue<int> temp(size);
                temp.push(q);
                delete q;
                q = temp;
                return;
            }
        }
};

int main() {
    queueApp a(1);
    a.enQueue(5);
    a.enQueue(4);
    return 0;
}