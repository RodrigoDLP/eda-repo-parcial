#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a = 1234567, b = 123456, c = 1234;
// <>, <<, >>

bool backtrack(ll n, int level) {

    int startlevel = level;
    if (n == 0) return true;
    if (n < c) return false;
    cout << n << "\n";
    bool a1 = (level >= 1 && backtrack((n-a), 1));
    if (a1){level = startlevel; return true;}
    ++level;
    bool b1 = (level >= 2 && backtrack(n-b, 2));
    if (b1) {level = startlevel; return true;}
    ++level;
    bool c1 = backtrack(n-((n/c)*c), 3);
    level = startlevel; return c1;
}
int main2() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n; cin >> n;

    if (n % 2 == 1) n -= a;
    bool output = backtrack(n, 1);
    if (output) cout << "YES\n";
    else cout << "NO\n";

}

bool verify(ll n) {
    ll num = n;
    while (num > 0 && num % 1234 != 0) {
        num -= 123456;
        if (num % 1234 == 0) return true;
    }
    return false;
}



int main3() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n; cin >> n;
    while (n > 0 && !verify(n)) {n -= 1234567;}
    if (n < 0) cout << "NO\n";
    else cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n; cin >> n;
    for (ll i=0; i*1234567 <= n; ++i) {
        ll a = i*1234567;
        for (ll j=0; a+j*123456 <= n; ++j) {
            ll r = n- (a+j*123456);
            if (r % 1234 == 0) {cout << "YES\n"; return 0;}
        }
    }
    cout << "NO\n";
}


