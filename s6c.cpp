#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;




int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int h, w; cin >> h >> w;
    vector<vector<ll>> v(h+1, vector<ll>(w+1, 0));
    for (int i=1; i<=h; ++i) {
        for (int j=1; j<=w; ++j) {
            char temp; cin >> temp;
            if (temp == '#') v[i][j] = 0;
            else if (i == 1 && j == 1) v[i][j] = 1;
            else v[i][j] = (v[i][j-1] + v[i-1][j]) % mod;
        }
    }
    cout << v[h][w] << "\n";
}