#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

// <>, <<, >>
int main() {
    //ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, temp; cin >> n; vector<int> v;
        for (int i=0; i<n; ++i) {cin >> temp; v.push_back(temp);}
        vector<int> output(n, -1);
        bool invalid = false;
        vector<pair<int, int>> poss;
        for (int i=0; i<n; ++i) {
            if (v[i] == 0) output[i] = 1;
            else if (v[i] != -1) {
                if (i-v[i] >= 0 && output[i] < 0 || i+v[i] < v.size()) {poss.emplace_back(i-v[i], i+v[i]); output[i-v[i]] = -2; output[i+v[i]] = -2;}
                else if (i-v[i] >= 0 && output[i] < 0) {output[i-v[i]] = 1;}
                else if (i+v[i] < v.size()) {output[i+v[i]] = 1;}
                else invalid = true;
                for (int i1=i-v[i]+1; i1<i+v[i]; ++i1) {
                    if (i1 == )
                }
            }
        }


    }
    return 0;
}



/*

for (int i=0; i <n; ++i){cin >> temp;
            if (temp % 2 == 1) {
                if (!modd.count(temp)) modd[temp] = 1; else modd[temp]++;
                if (!modd.count(temp-2)) modd[temp-2] = 1; else modd[temp-2]++;
            }
            else {
            if (!m.count(temp)) m[temp] = 1; else m[temp]++;
        }}
        int maxval = 0;
        for (auto e: modd) if (e.second > maxval) maxval = e.second;
        for (auto e: m) if (e.second > maxval) maxval = e.second;
        cout << maxval << "\n";
 */