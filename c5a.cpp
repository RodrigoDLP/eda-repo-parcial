#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;



// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b, c, m; cin >> a >> b >> c >> m;
    deque<pair<int, char>> v;
    int temp; string stemp;
    for (int i=0; i<m; ++i) {
        cin >> temp >> stemp; if (stemp == "USB") v.emplace_back(temp, 'U'); else v.emplace_back(temp, 'P');
    }
    sort(v.begin(), v.end());
    ll count=0, price=0;
    while (!v.empty() && !(a==0 && b==0 && c==0)) {
        pair<int, char> p = v.front(); v.pop_front();
        if (p.second == 'U') {
            if (a > 0) {a--; count++; price += p.first;}
            else if (c > 0) {c--; count++; price += p.first;}
        } else {
            if (b > 0) {b--; count++; price += p.first;}
            else if (c > 0) {c--; count++; price += p.first;}
        }
    }
    cout << count << " " << price << "\n";
    return 0;
}