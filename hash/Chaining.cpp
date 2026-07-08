#include <bits/stdc++.h>
using namespace std;

class HashTableChaining {
private:
    vector<list<pair<string,int>>> table;
    int cap;

    int hashFunc(const string& key) const {
        return (hash<string>{}(key) & 0x7fffffff) % cap;
    }

public:
    HashTableChaining(int c = 8) : cap(c) {
        table.resize(cap);
    }

    void put(const string& key, int value) {
        int i = hashFunc(key);
        for (auto& kv : table[i]) {
            if (kv.first == key) { kv.second = value; return; }
        }
        table[i].push_back({key, value});
    }

    bool get(const string& key, int& outVal) {
        int i = hashFunc(key);
        for (auto& kv : table[i]) {
            if (kv.first == key) { outVal = kv.second; return true; }
        }
        return false;
    }

    void remove(const string& key) {
        int i = hashFunc(key);
        table[i].remove_if([&](auto& kv){ return kv.first == key; });
    }
};
