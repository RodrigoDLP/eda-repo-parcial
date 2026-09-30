#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;



// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll a; cin >> a;
    ll b, c; cin >> b >> c;
    ll m; cin >> m; ll temp; string stemp;
    deque<ll> usb, ps2;
    for (ll i=0; i<m; ++i) {
        cin >> temp; cin >> stemp;
        if (stemp[0] == 'U') usb.push_back(temp); else ps2.push_back(temp);
    }
    sort(usb.begin(), usb.end()); sort(ps2.begin(), ps2.end());
    ll finalcost = 0, finalcount = 0;
    for (ll i=0; i<min(ll(a), ll(usb.size())); ++i) {auto e = usb.front(); finalcost += e; finalcount++; usb.pop_front();}
    for (ll i=0; i<min(ll(b), ll(ps2.size())); ++i) {auto e = ps2.front(); finalcost += e; finalcount++; ps2.pop_front();}
    deque<ll> v; for (auto e: usb) v.push_back(e); for (auto e: ps2) v.push_back(e);
    //return 0;
    sort(v.begin(), v.end());
    for (ll i=0; i<min(ll(c), ll(v.size())); ++i) {auto e = v.front(); finalcost += e; finalcount++; v.pop_front();}
    cout << finalcount << " " << finalcost << "\n";
    return 0;
}