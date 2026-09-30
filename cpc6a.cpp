#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T; cin >> T;
    while (T--) {
        map<pair<ll, ll>, ll> m1;
        ll n, x, y; cin >> n >> x >> y;
        vector<ll> v1;
        for (ll i=0; i<n; ++i) {
            ll temp; cin >> temp; v1.push_back(temp);
            auto pair = make_pair(temp % x, temp % y);
            if (m1.count(pair)) m1[pair]++; else m1[pair] = 1;
            //m2[pair].emplace_back(pair);
        }
        ll counter = 0;
        for (ll i=0; i<n; ++i) {
            auto pair = make_pair((x - (v1[i] % x)) % x, v1[i] % y);
            if (m1.count(pair)) {
                counter += m1[pair];
                //cout << "current pair: " << pair.first << ", " << pair.second << ", found=" << m1[pair] << "\n";
                if (v1[i] % x == (x - (v1[i] % x)) % x) --counter;
            }

        }
        cout << counter/2 << "\n";

    }
}