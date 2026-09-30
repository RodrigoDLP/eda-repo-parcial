#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, m, k; cin >> n >> m >> k;
        string output;
        if (abs(n-m) > k || k > m && k > n) {cout << -1 << "\n"; continue;}

            if (n > m) {
                if (n-k > m) {cout << -1 << "\n"; continue;}
                for (int i=0; i<k; ++i) output += "0";
                for (int i=0; i<n-k; ++i) output += "10";
                for (int i=0; i<m-(n-k); ++i) output += "1";
                cout << output << "\n"; continue;
            } else {
                if (m-k > n) {cout << -1 << "\n"; continue;}
                for (int i=0; i<k; ++i) output += "1";
                for (int i=0; i<m-k; ++i) output += "01";
                for (int i=0; i<n-(m-k); ++i) output += "0";
                cout << output << "\n"; continue;
            }

    }
}