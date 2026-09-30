#include <bits/stdc++.h>
using namespace std;


int dp(int i, int w, vector<int>& values, vector<int>& weights, vector<vector<int>>& m) {
    if (w < 0) return -INT_MAX;
    if (i == 0) return 0;
    if (m[i][w] != -1) return m[i][w];
    m[i][w] = max(dp(i-1, w, values, weights, m), dp(i-1, w-weights[i], values, weights, m) + values[i]);
    return m[i][w];
}


int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, W; cin >> n >> W;
    vector<int> values(n+1), weights(n+1);
    vector<vector<int>> m(n+1, vector<int>(W+1, -1));
    m[0][0] = 0;
    for (int i=1; i<=n; ++i) {
        cin >> values[i]; cin >> weights[i];
    }
    cout << dp(n, W, values, weights, m) << "\n";
}