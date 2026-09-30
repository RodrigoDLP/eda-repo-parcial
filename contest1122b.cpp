#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T; cin >> T;
    while (T--) {
        ll a, b, c; cin >> a >> b >> c;
        if (abs(a+c-b) < abs(a-b)) {cout << abs(a-b) << "\n"; continue;}
        cout << abs(a+c-b) << "\n";
    }
}