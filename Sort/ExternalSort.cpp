#include <bits/stdc++.h>
using namespace std;

void externalSort(vector<int>& data, int chunkSize) {
    vector<vector<int>> runs;
    for (int i=0;i<data.size();i+=chunkSize) {
        int end = min((int)data.size(), i+chunkSize);
        vector<int> chunk(data.begin()+i, data.begin()+end);
        sort(chunk.begin(), chunk.end());
        runs.push_back(chunk);
    }
    // multi-way merge
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
    vector<int> idx(runs.size(),0);
    for (int i=0;i<runs.size();i++) if (!runs[i].empty())
        pq.push({runs[i][0],i});
    vector<int> result;
    while(!pq.empty()) {
        auto [val,i]=pq.top(); pq.pop();
        result.push_back(val);
        idx[i]++;
        if (idx[i]<runs[i].size())
            pq.push({runs[i][idx[i]],i});
    }
    data = result;
}

int main() {
    vector<int> data = {50,20,70,10,90,40,30,80,60};
    cout << "Before sort: ";
    for (int x:data) cout<<x<<" "; cout<<"\n";
    externalSort(data, 3); // giả sử RAM chỉ chứa 3 phần tử
    cout << "After sort: ";
    for (int x:data) cout<<x<<" "; cout<<"\n";
}
