#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


/*
int dpf(int i, int j, string& s1, string& s2, vector<vector<int>>& dp) {
    //if (i < 0 || j < 0) return -INT_MAX;
    if (dp[i][j] != -1) return dp[i][j];
    if (i == 0 || j == 0) {dp[i][j] = 0; return 0;}
    if (i > 0 && j > 0 && s1[i-1] == s2[i-1]) dp[i][j] = dpf(i-1, j-1, s1, s2, dp) + 1;
    else dp[i][j] = max(dpf(i-1, j, s1, s2, dp), dpf(i, j-1, s1, s2, dp));
    return dp[i][j];
}*/


int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        string s1, s2; cin >> s1 >> s2;
        vector<vector<int>> dp(s1.size()+1, vector<int>(s2.size()+1, 0));
        //cout << dpf(s1.size(), s2.size(), s1, s2, dp) << "\n";
        for (int i=1; i<=s1.size(); ++i) {
            for (int j=1; j<=s2.size(); ++j) {
                if (s1[i-1] == s2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        cout << dp[s1.size()][s2.size()] << "\n";
    }
}
