#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, m, temp;
        ll maxprod = 0;
        deque<int> impact;
        vector<int> prod;
        cin >> n; cin >> m;
        for (int i=0; i<n; ++i) {cin >> temp; prod.push_back(temp);}
        for (int i=0; i<m; ++i) {cin >> temp; impact.push_back(temp);}
        sort(impact.begin(), impact.end(), greater<int>());
        int i = prod.size();
        while (i > impact[0]) {
            maxprod += prod[i-1];
            --i;
        }
        while (impact.size() >= 2) {
            ll k = 0;
            while (i > impact[1]) {k += prod[i-1]; --i;}
            maxprod += abs(k);
            impact.pop_front();
        }
        ll k = 0;
        while (i > 0) {k += prod[i-1]; --i;}
        maxprod += abs(k);
        cout << maxprod << "\n";
    }
    return 0;
}
