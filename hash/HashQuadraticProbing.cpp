// băm thăm dò bậc 2
#include <bits/stdc++.h>
using namespace std;

class HashTableQuadratic {
    int cap;
    vector<string> table;
    vector<bool> used;
    int hashFunc(const string& key) const {
        return (hash<string>{}(key) & 0x7fffffff) % cap;
    }
public:
    HashTableQuadratic(int c=7) : cap(c), table(c), used(c,false) {}
    void insert(const string& key) {
        int idx = hashFunc(key);
        for (int i=0; i<cap; i++) {
            int j = (idx + i*i) % cap;
            if (!used[j]) { table[j] = key; used[j] = true; return; }
        }
        cout << "Table full!\n";
    }
    bool search(const string& key) {
        int idx = hashFunc(key);
        for (int i=0;i<cap;i++) {
            int j = (idx+i*i)%cap;
            if (!used[j]) return false;
            if (table[j]==key) return true;
        }
        return false;
    }
    void display() {
        for (int i=0;i<cap;i++) cout << i << ": " << (used[i]?table[i]:"NULL") << endl;
    }
};

int main() {
    HashTableQuadratic ht(7);
    ht.insert("apple");
    ht.insert("banana");
    ht.insert("grape");
    ht.display();
    cout << "Search apple: " << (ht.search("apple")?"found":"not found") << endl;
}
