#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; string s; cin >> n >> s;
        int onecounter = 0;
        vector<int> ratio1(n), ratio2(n);

        for (int i=0; i<s.size(); ++i) {
            char c1 = s[i];
            if (i == 0) {
                if (c1 == '1') ratio1[0] = 1; else ratio1[0] = 0;
            }
            else if (c1 == '1') {ratio1[i] = ratio1[i-1]+1;}
            else ratio1[i] = ratio1[i-1];
            if (c1 == '1') ++onecounter;
        }
        for (int i=n-1; i>=0; --i) {
            char c1 = s[i];
            if (i == n-1) {
                if (c1 == '1') ratio2[n-1] = 0; else ratio2[n-1] = 1;
            }
            else if (c1 == '0') {ratio2[i] = ratio2[i+1]+1;}
            else ratio2[i] = ratio2[i+1];
        }
        if (s[0] == '1') {cout << ratio2[0] << "\n"; continue;}
        if (ratio1[n-1] == 0) {cout << 0 << "\n"; continue;}
        int minsum = INT_MAX;
        for (int i=0; i<n-1; ++i) {
            if (ratio1[i] + ratio2[i+1] < minsum) minsum = ratio1[i] + ratio2[i+1];
        }
        cout << min(minsum, onecounter) << "\n";
    }
}