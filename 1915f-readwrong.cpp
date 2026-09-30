#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int t1, t2; vector<int> v3;
        unordered_map<int, bool> lefties, righties;
        for (int i=0; i<n; ++i) {
            cin >> t1>>t2;
            v3.push_back(t1); v3.push_back(t2);
            if (t1 > t2) {lefties[t2] = true; lefties[t1] = false;}
            else {righties[t1] = true; righties[t2] = false; }
        }
        sort(v3.begin(), v3.end());
        cout << v3.size() << " es el tam\n";
        int left = 0; int right = 0;
        ll output = 0;
        for (auto e: v3) {
            if (righties.count(e)) {
                if (righties[e]) {
                    ++right;
                } else {
                    --right;
                }
                output += left;
            }
            else {
               if (lefties[e]) {
                   ++left;
               } else {
                   --left;
               }
                output += right;
            }
            if (left < 0 || right < 0) return -123;
        }
        cout << output/2 << "\n";
    }
}