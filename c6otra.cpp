#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    vector<ll> a(n);
    for (int i=0; i<n; ++i) cin >> a[i];
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int i=0; i<n; ++i) dp[i][i] = a[i];
    for (int len=2; len<=n; ++len) {
        for (int i=0; i<=n-len; ++i) {
            int j = i+len-1;
            dp[i][j] = max(a[i]-dp[i+1][j], a[j]-dp[i][j-1]);
        }
    }
    cout << dp[0][n-1] << "\n";
}