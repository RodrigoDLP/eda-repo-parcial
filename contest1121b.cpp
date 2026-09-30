#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        ll sum = 0;
        vector<int> v(n);
        for (int i=0; i<n; ++i) cin >> v[i];
        sort(v.begin(), v.end());
        vector<__int128> linearfactorial(n+1); // from 1
        linearfactorial[0] = 1;
        for (int i=1; i<=n; ++i) linearfactorial[i] = i * linearfactorial[i-1];

        vector<__int128> elementsums(n+1); elementsums[n] = v[n-1];
        for (int i=n-1; i>0; --i) elementsums[i] = v[i-1] + elementsums[i+1];

        __int128 subtract = elementsums[elementsums.size()-1] * linearfactorial[n];
        __int128 cum = 0;
        for (int i=2; i<=n; ++i) cum += (linearfactorial[n] / (n-i+1)) * elementsums[i];
        ll result = (cum-subtract) % 998244353;
        cout << result << "\n";
    }
}