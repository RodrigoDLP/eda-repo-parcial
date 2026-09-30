#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
typedef long double ld;


bool count(const ll& t, const ll& n, const ll& x, const ll& y) {
    __int128 myn = n;
    ll xcount = t / x;
    ll ycount = t / y;
    __int128 a = xcount * ycount;
    return a >= myn;
}


//ult verd:
/*
while (lo < hi) {
    ll mi = lo + (hi-lo+1)/2;
    if (pred que se cumple para izq) lo = mi; else hi = mi-1;
}
if (pred que se cumple para izq es FALSO) cout << -1 << "\n";
else cout << lo << "\n";
*/
/*
//primer falso:
while (lo < hi) {
    ll mi = lo + (hi-lo)/2;
    if (pred que se cumple para izq) lo = mi+1; else hi = mi;
}
if (pred que se cumple para izq es VERDADERO) cout << -1 << "\n";
else cout << lo << "\n";
*/



// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        long long w; cin >> w;
        long long h; cin >> h;
        long long n; cin >> n;
        ll lo = 1;
        ll hi = max(w, h)*n;
        ll mi = 0;
        while (lo < hi) {
            mi = lo + (hi-lo)/2;
            if (!count(mi, n, w, h)) lo = mi+1; else hi = mi;
        }
        if (!count(lo, n, w, h)) throw runtime_error("-1");
        else cout << static_cast<long long>(lo) << "\n";
    }
    return 0;
}
