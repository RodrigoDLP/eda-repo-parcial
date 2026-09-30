#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;


bool count(ll& t, ll& k, vector<ll>& v) {
    ll i = v.size() / 2;
    if (i >= v.size() || i < 0) throw runtime_error("???");
    if (v[i] >= t) return true;
    //cout << "HOla2\n";
    ll diffsum = 0;
    if (i >= v.size() || i < 0) throw runtime_error("?");
    while (i < v.size() && v[i] < t) {
        if (i >= v.size() || i <0) throw runtime_error("??");
        diffsum += t-v[i]; ++i;
        //if (i >= v.size() || i <0) throw runtime_error("????");
    }
    //cout << "HOla3\n";
    return (diffsum <= k);
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
    //ios::sync_with_stdio(false);
    cin.tie(nullptr);

        ll n; cin >> n;
        ll k; cin >> k;
        ll temp;
        vector<ll> v; for (int i = 0; i<n; ++i) {cin>>temp; v.push_back(temp);}
        sort(v.begin(), v.end());
        //cout << v.size();
        if (v.empty()) throw runtime_error("empty");
        ll lo = 0, hi = v[v.size()-1]+k;
        while (lo < hi) {
            ll mi = lo + (hi-lo+1)/2;
            if (count(mi, k, v)) lo = mi; else hi = mi-1;
            //cout << "lo: " << lo << " hi: " << hi << " mi: " << mi << "\n ";
        }
        if (!count(lo, k, v)) throw runtime_error("-1");
        else cout << lo << "\n";
    return 0;
}
