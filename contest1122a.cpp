#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n; int m = n;
        for (int i=0; i<3; ++i) {
            int temp; cin >> temp;
            if (temp < m) m = temp;
        }
        cout << n-m << "\n";
    }
}