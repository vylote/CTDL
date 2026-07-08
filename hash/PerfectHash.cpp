#include <bits/stdc++.h>
using namespace std;

class PerfectHash {
    vector<int> table;
    int n;
    int hashFunc(int key) const { return key % n; }
public:
    PerfectHash(const vector<int>& keys) {
        n = keys.size();
        table.assign(n, -1);
        for (int k : keys) {
            int idx = hashFunc(k);
            if (table[idx] != -1) {
                cerr << "Not perfect hash!\n";
                return;
            }
            table[idx] = k;
        }
    }
    bool search(int key) {
        int idx = hashFunc(key);
        return table[idx]==key;
    }
    void display() {
        for (int i=0;i<n;i++)
            cout << i << ": " << table[i] << endl;
    }
};

int main() {
    vector<int> keys = {7, 14, 21}; // không va chạm khi mod 3
    PerfectHash ph(keys);
    ph.display();
    cout << "Search 14: " << (ph.search(14)?"found":"not found") << endl;
}
