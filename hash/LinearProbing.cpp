#include <bits/stdc++.h>
using namespace std;

class HashTableLinear {
    int cap;
    vector<string> table;
    vector<bool> used;
    int hashFunc(const string& key) const {
        return (hash<string>{}(key) & 0x7fffffff) % cap;
    }
public:
    HashTableLinear(int c=7) : cap(c), table(c), used(c,false) {}
    void insert(const string& key) {
        int idx = hashFunc(key);
        for (int i=0; i<cap; i++) {
            int j = (idx + i) % cap;
            if (!used[j]) { table[j] = key; used[j] = true; return; }
        }
        cout << "Table full!\n";
    }
    bool search(const string& key) {
        int idx = hashFunc(key);
        for (int i=0; i<cap; i++) {
            int j = (idx+i)%cap;
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
    HashTableLinear ht(7);
    ht.insert("apple");
    ht.insert("banana");
    ht.insert("grape");
    ht.display();
    cout << "Search grape: " << (ht.search("grape")?"found":"not found") << endl;
}
