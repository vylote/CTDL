#include <bits/stdc++.h>
using namespace std;

//queue biểu diễn dạng vòng

template<class T>
class Queue{
    private:
        T* Q;
        int N,f,r;
    public:
        Queue(int n = 2) : N(n) {
            f = r = 0;
            Q = new T[n];
        }
        ~Queue() {delete[] Q;}
        bool empty() {return f==r;}
        int size() {return (N-f+r)%N;}
        T front() {return Q[f];}
        T back() {return r==0?Q[N-1]:Q[r-1];}
        void push(T o) {
            if (size() == N-1) {
                int M = N*2+2;
                T* tmp = new T[M];
                for (int i = f, j=0;i<f+N-1;++i) tmp[j++]=Q[i%N];
                f = 0;
                r = f+N-1;
                delete[] Q;
                Q = tmp;
                N = M;
            }
            Q[r] = o;
            r = (r+1)%N;
        }
        void pop() {
            f = (f+1)%N; 
        }
};

int main() {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.front() << " " << q.back() << "\n";
    q.pop();
    cout << q.front() << " " << q.back();
}