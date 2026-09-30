#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        map<pair<int, int>, int> m1;
        int n, x, y; cin >> n >> x >> y;
        vector<int> v1;
        ll counter = 0;
        for (int i=0; i<n; ++i) {
            int temp; cin >> temp; v1.push_back(temp);
            auto pair = make_pair(temp % x, temp % y);
            auto pair2 = make_pair((x - (temp % x)) % x, temp % y);
            if (m1.count(pair2)) counter += m1[pair2];
            if (m1.count(pair)) m1[pair]++; else m1[pair] = 1;
        }
        cout << counter << "\n";
    }
}