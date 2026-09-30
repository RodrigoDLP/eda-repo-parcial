#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



//<>
int dpf(int i, int j, vector<ll>& a, vector<vector<ll>>& dp) {
    if (dp[i][j] != -INT_MAX) return dp[i][j];

    if (i == j) dp[i][j] = a[i];
    else dp[i][j] =max(a[i]-dpf(i+1, j, a, dp), a[j]-dpf(i, j-1, a, dp));
    return dp[i][j];
}


int main() {
    cin.tie(0) -> sync_with_stdio(false);
    ll l; cin >> l;
    vector<ll> v(l);
    vector<vector<ll>> dp(l, vector<ll>(l, -INT_MAX));
    for (int i = 0; i < l; ++i) {
        cin >> v[i];
    }
    if (l == 1) {cout << v[0] << "\n"; return 0;}
    dpf(0, l-1, v, dp);
    ll sum = 0;

    cout << dp[0][l-1] << "\n";

}