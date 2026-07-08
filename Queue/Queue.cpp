#include <bits/stdc++.h>
using namespace std;
//cai dat queue bang mang
template<class T>

class Queue {
    T *buff;
    int num, N, F, L; //L chi luu tru den last-1
public:
    Queue<T>() {
        num = N = F = L = 0;
        buff = NULL;
    }
    ~Queue<T>() {
        if (buff) delete[] buff;
    }
    void push(T x) {
        if (num == N) reserve(N*2+2);
        buff[L] = x; L = (L+1)%N; num++;
    }
    void pop() {
        F = (F+1)%N; num--;
    }
    T& front() {
        return buff[F];
    }
    T& back() {
        return L == 0 ? buff[N-1] : buff[L-1];
    }
    void reserve(int newcap) {
        if (newcap <= N) return;
        T *tem = new T[newcap];
        for (int i = F, j = 0; i < F+num; ++i) tem[j++] = buff[i%N];
        F = 0;
        L = num+F;
        if (buff) delete buff;
        buff = tem;
        N = newcap;
    }
    int size() {
        return num;
    }
    bool isEmpty() {
        return (num == 0) ? true : false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Queue<int> a;
    a.push(1);
    a.push(2);
    a.push(3);
    cout << a.isEmpty() << " " << a.size();
    return 0;
}