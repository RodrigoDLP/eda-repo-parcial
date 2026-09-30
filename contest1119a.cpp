#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;


// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        int counter = 0;
        for (int i=0; i<n; i += k) {
            bool allones = true;
            for (int j=i; j<i+k; ++j) if (s[j] == '0') allones = false;
            if (allones) ++counter;
        }
        cout << counter << "\n";
    }
    return 0;
}
