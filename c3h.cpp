#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<string> nums; string temp;
    for (int i=0; i<n; ++i) {cin >> temp; nums.push_back(temp);}
    unordered_map<int, pair<int, int>> u1;
    for (int i=0; i<k; ++i) {
        int min_local = 10;
        pair<int, int> p;
        for (int n1 = 0; n1 < k; ++n1) {
            for (int n2 = 0; n2 < k; ++n2) {
                if (n1 != n2) {
                    if (!u1.count(make_pair(n1, n2)) {
                        if (n1[i] - n2[i] < min_local) min_local = n1[i] - n2[i];

                }
            }
        }
    }
}