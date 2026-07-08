#include <bits/stdc++.h>
using namespace std;

template<typename K, typename V>
class Dictionary {
    struct Entry { K key; V value; bool used=false; };
    int cap;
    vector<Entry> table;
    int hashFunc(const K& key) const {
        return (hash<K>{}(key) & 0x7fffffff) % cap;
    }
public:
    Dictionary(int c=7): cap(c), table(c) {}
    void insert(const K& key, const V& value) {
        int idx = hashFunc(key);
        for (int i=0;i<cap;i++) {
            int j = (idx+i)%cap;
            if (!table[j].used) { table[j]={key,value,true}; return; }
        }
        cout << "Table full!\n";
    }
    V* search(const K& key) {
        int idx = hashFunc(key);
        for (int i=0;i<cap;i++) {
            int j=(idx+i)%cap;
            if (!table[j].used) return nullptr;
            if (table[j].key==key) return &table[j].value;
        }
        return nullptr;
    }
    void display() {
        for (int i=0;i<cap;i++) {
            if (table[i].used)
                cout << i << ": " << table[i].key << " => " << table[i].value << endl;
            else cout << i << ": NULL\n";
        }
    }
};

int main() {
    Dictionary<string,string> dict(7);
    dict.insert("apple","táo");
    dict.insert("banana","chuối");
    dict.display();
    auto v = dict.search("banana");
    cout << "banana = " << (v?*v:"not found") << endl;
}
