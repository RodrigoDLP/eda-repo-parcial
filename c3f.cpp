#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int a, b, c; cin >> a >> b >> c;
        if (a > b || a == b && c % 2 == 1) cout << "First\n";
        else cout << "Second\n";
    }
}